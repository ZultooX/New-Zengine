#include "RenderTarget.h"

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#include <d3d11.h>

#include "DepthBuffer.h"


void RenderTarget::Create(const D3D11_TEXTURE2D_DESC* aTextureDesc, const D3D11_RENDER_TARGET_VIEW_DESC* aRTVDesc, const std::string& aName)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	ge->GetDevice()->CreateTexture2D(aTextureDesc, nullptr, &myTexture);
	ge->GetDevice()->CreateRenderTargetView(myTexture, aRTVDesc, &myRTV);
	ge->GetDevice()->CreateShaderResourceView(myTexture, nullptr, &mySRV);

	myRTV->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(aName.length() + 1), aName.c_str());
	mySRV->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(aName.length() + 1), aName.c_str());
}

void RenderTarget::Create(const Vector2i& aSize, const DXGI_FORMAT aFormat, const std::string& aName )
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = aSize.x;
	desc.Height = aSize.y;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = aFormat;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ge->GetDevice()->CreateTexture2D(&desc, nullptr, &myTexture);
	ge->GetDevice()->CreateRenderTargetView(myTexture, nullptr, &myRTV);
	ge->GetDevice()->CreateShaderResourceView(myTexture, nullptr, &mySRV);

	myRTV->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(aName.length() + 1), aName.c_str());
	mySRV->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(aName.length() + 1), aName.c_str());
}

void RenderTarget::SetAsActiveTargetOnSlot(const DepthBuffer* aDSV)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	if(aDSV)ge->GetContext()->OMSetRenderTargets(1, &myRTV, aDSV->GetDSV());
	else ge->GetContext()->OMSetRenderTargets(1, &myRTV, nullptr);
}

void RenderTarget::Clear(const Color& aColor)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	ge->GetContext()->ClearRenderTargetView(myRTV, aColor.GetPtr());
}
