#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#include <Engine/ComponentSystem/ComponentManager.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/Utilities/MainSingleton.h>
#include <GraphicsEngine/DX11/Drawers/MeshDrawer.h>
#include <GraphicsEngine/DX11/Buffers/BufferManager.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>

#include <GraphicsEngine/DX11/Rendering/RenderPass/RenderPassManager.h>

#include <Shaders/Common/ConstantBuffers.h>


#ifdef USE_DX11
extern HWND gHWND;


bool DX11GraphicsEngine::Initialize()
{
	const EngineSettings& settings = Engine::GetSettings();

	if (!CreateDeviceAndSwapchain()) return false;
	if (!CreateRenderTarget()) return false;
	if (!CreateDepthStencil()) return false;
	if (!CreateTextureSamplers()) return false;

	myViewPort.TopLeftX = 0.f;
	myViewPort.TopLeftY = 0.f;
	myViewPort.Width = static_cast<float>(settings.GetResolution().x);
	myViewPort.Height = static_cast<float>(settings.GetResolution().y);
	myViewPort.MinDepth = 0.f;
	myViewPort.MaxDepth = 1.f;

	myContext->RSSetViewports(1, &myViewPort);
	myContext->OMSetRenderTargets(1, &myBackBuffer, myDepthBuffer);

	MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().Init();
	MainSingleton::GetInstance<RenderPassManager>().Init();

	return true;
}

void DX11GraphicsEngine::Present()
{
	mySwapChain->Present(1, 0);
}

#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

void DX11GraphicsEngine::OnResize()
{

}


void DX11GraphicsEngine::Cleanup()
{
	if (myBackBuffer) 
	{
		myBackBuffer->Release();
		myBackBuffer = nullptr;
	}

	if (myDepthBuffer) 
	{
		myDepthBuffer->Release();
		myDepthBuffer = nullptr;
	}

	if (mySRV) 
	{
		mySRV->Release();
		mySRV = nullptr;
	}

	if (myDefaultSampler) 
	{
		myDefaultSampler->Release();
		myDefaultSampler = nullptr;
	}

	if (mySwapChain) 
	{
		mySwapChain->Release();
		mySwapChain = nullptr;
	}

	if (myDevice) 
	{
		myDevice->Release();
		myDevice = nullptr;
	}

	if (myContext) 
	{
		myContext->Release();
		myContext = nullptr;
	}
}

bool DX11GraphicsEngine::CreateDepthStencil()
{
	ID3D11Texture2D* backBuffTexture = nullptr;
	mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffTexture);

	D3D11_TEXTURE2D_DESC desc;
	backBuffTexture->GetDesc(&desc);

	backBuffTexture->Release();

	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32_TYPELESS;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ID3D11Texture2D* texture;
	HRESULT result = myDevice->CreateTexture2D(&desc, nullptr, &texture);
	if (result != S_OK) return false;

	ID3D11DepthStencilView* DSV;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};

	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	result = myDevice->CreateDepthStencilView(texture, &dsvDesc, &DSV);
	if (result != S_OK) return false;

	ID3D11ShaderResourceView* SRV;
	D3D11_SHADER_RESOURCE_VIEW_DESC srDesc{};
	srDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
#undef max
	srDesc.Texture2D.MipLevels = std::numeric_limits<UINT>::max();
	result = myDevice->CreateShaderResourceView(texture, &srDesc, &SRV);

	return SUCCEEDED(result);
}

bool DX11GraphicsEngine::CreateDeviceAndSwapchain()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = gHWND;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true;

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&mySwapChain,
		&myDevice,
		nullptr,
		&myContext
	);

	return SUCCEEDED(result);
}

bool DX11GraphicsEngine::CreateRenderTarget()
{
	ID3D11Texture2D* backBuffTexture = nullptr;
	mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffTexture);

	HRESULT result = myDevice->CreateRenderTargetView(
		backBuffTexture,
		nullptr,
		&myBackBuffer);

	return SUCCEEDED(result);
}

bool DX11GraphicsEngine::CreateTextureSamplers()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0.0f;
	samplerDesc.BorderColor[1] = 0.0f;
	samplerDesc.BorderColor[2] = 0.0f;
	samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	myDevice->CreateSamplerState(&samplerDesc, &myDefaultSampler);

	myContext->PSSetSamplers(0, 1, &myDefaultSampler);
	return true;
}

bool DX11GraphicsEngine::PreUpdate()
{
	constexpr float CLEAR_COLOR[] = { 0.f, 0.f, 0.f, 1.f };
	myContext->ClearRenderTargetView(myBackBuffer, CLEAR_COLOR);
	if (myDepthBuffer)
	{
		myContext->ClearDepthStencilView(myDepthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	myContext->OMSetRenderTargets(1, &myBackBuffer, myDepthBuffer);

	return true;
}




bool DX11GraphicsEngine::MainUpdate()
{
	Zengine::ComponentSystem::Camera* cam = Zengine::ComponentSystem::Camera::MainCamera;

	if (!cam) return true;

	cam->SetPerspectiveView();

	cam->gameobject->transform->UpdateTransformMatricies();
	MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateFrameBuffer(cam->inverseView, cam->projectionMatrix, { 0.f, 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f ,0.f });

	return true;
}

bool DX11GraphicsEngine::PostUpdate()
{
	MainSingleton::GetInstance<RenderPassManager>().Render();
	myContext->OMSetRenderTargets(1, &myBackBuffer, myDepthBuffer);

	return true;
}

ID3D11DeviceContext* DX11GraphicsEngine::GetContext() { return myContext; }
IDXGISwapChain* DX11GraphicsEngine::GetSwapChain() { return mySwapChain; }
ID3D11Device* DX11GraphicsEngine::GetDevice() { return myDevice; }
ID3D11RenderTargetView* DX11GraphicsEngine::GetRTV() { return myBackBuffer; }
ID3D11DepthStencilView* DX11GraphicsEngine::GetDSV() { return myDepthBuffer; }
ID3D11ShaderResourceView* DX11GraphicsEngine::GetSRV() { return mySRV; }

void DX11GraphicsEngine::SetBackBufferAsTarget()
{
	myContext->OMSetRenderTargets(1, &myBackBuffer, nullptr);
}

void DX11GraphicsEngine::CreateBuffer(ID3D11Buffer** aBuffer, const D3D11_BUFFER_DESC& aBufferDescription, const D3D11_SUBRESOURCE_DATA& someData)
{
	HRESULT res = myDevice->CreateBuffer(&aBufferDescription, &someData, aBuffer);
	assert(SUCCEEDED(res));
}
#endif // USE_DX11