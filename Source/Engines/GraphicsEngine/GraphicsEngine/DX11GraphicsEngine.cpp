#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#ifdef USE_DX11
extern HWND gHWND;


bool DX11GraphicsEngine::Initialize()
{
	const EngineSettings& settings = Engine::GetSettings();

	if (!CreateDeviceAndSwapchain()) return false;
	if (!CreateRenderTarget()) return false;
	if (!CreateDepthStencil()) return false;

	myViewPort.TopLeftX = 0.f;
	myViewPort.TopLeftY = 0.f;
	myViewPort.Width = static_cast<float>(settings.GetResolution().x);
	myViewPort.Height = static_cast<float>(settings.GetResolution().y);
	myViewPort.MinDepth = 0.f;
	myViewPort.MaxDepth = 1.f;

	myContext->RSSetViewports(1, &myViewPort);
	myContext->OMSetRenderTargets(1, &myBackBuffer, myDepthBuffer);

	return true;
}

void DX11GraphicsEngine::Present()
{
	mySwapChain->Present(1, 0);
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

bool DX11GraphicsEngine::PreUpdate()
{
	constexpr float CLEAR_COLOR[] = { 0.f, 0.f, 0.f, 1.f };
	myContext->ClearRenderTargetView(myBackBuffer, CLEAR_COLOR);
	myContext->ClearDepthStencilView(myDepthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);


	return true;
}

bool DX11GraphicsEngine::MainUpdate()
{
	myContext->OMSetRenderTargets(1, &myBackBuffer, myDepthBuffer);
	return true;
}

bool DX11GraphicsEngine::PostUpdate()
{
	return true;
}

ID3D11DeviceContext* DX11GraphicsEngine::GetContext() { return myContext; }
IDXGISwapChain* DX11GraphicsEngine::GetSwapChain() { return mySwapChain; }
ID3D11Device* DX11GraphicsEngine::GetDevice() { return myDevice; }
ID3D11RenderTargetView* DX11GraphicsEngine::GetRTV() { return myBackBuffer; }
ID3D11DepthStencilView* DX11GraphicsEngine::GetDSV() { return myDepthBuffer; }
ID3D11ShaderResourceView* DX11GraphicsEngine::GetSRV() { return mySRV; }

void DX11GraphicsEngine::CreateBuffer(ID3D11Buffer** aBuffer, const D3D11_BUFFER_DESC& aBufferDescription, const D3D11_SUBRESOURCE_DATA& someData)
{
	myDevice->CreateBuffer(&aBufferDescription, &someData, aBuffer);
}
#endif // USE_DX11