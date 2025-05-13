#include "DepthBuffer.h"

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>
#include <d3d11.h>

void DepthBuffer::Create(const Vector2i& aSize)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	D3D11_TEXTURE2D_DESC desc = { 0 };
	desc.Width = aSize.x;
	desc.Height = aSize.y;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32_TYPELESS;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ge->GetDevice()->CreateTexture2D(&desc, nullptr, &myTexture);

	//if (!myTexture) return;

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};

	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	ge->GetDevice()->CreateDepthStencilView(myTexture, &dsvDesc, &myDSV);


	D3D11_SHADER_RESOURCE_VIEW_DESC srDesc{};
	srDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srDesc.Texture2D.MostDetailedMip = 0;
#undef max
	srDesc.Texture2D.MipLevels = std::numeric_limits<UINT>::max();
	ge->GetDevice()->CreateShaderResourceView(myTexture, &srDesc, &mySRV);
}

void DepthBuffer::Clear()
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	ge->GetContext()->ClearDepthStencilView(myDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}
