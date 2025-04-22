#include "GBuffer.h"

#include <d3d11.h>
#include <Zultools/Math/Vector4.hpp>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#include <GraphicsEngine/DX11/IO/DepthBuffer.h>

GBuffer GBuffer::Create(Vector2i aSize)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	HRESULT result;

	std::array<DXGI_FORMAT, (int)GBufferTexture::Count> textureFormats = {
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		DXGI_FORMAT_R10G10B10A2_UNORM,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_R8G8B8A8_UNORM
	};

	GBuffer output;


	D3D11_TEXTURE2D_DESC desc = { 0 };
	desc.Width = aSize.x;
	desc.Height = aSize.y;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;


	for (unsigned int idx = 0; idx < (int)GBufferTexture::Count; idx++)
	{
		desc.Format = textureFormats[idx];
		result = ge->GetDevice()->CreateTexture2D(&desc, nullptr, &output.myTextures[idx]);
		//assert(SUCCEEDED(result));
		result = ge->GetDevice()->CreateRenderTargetView(
			output.myTextures[idx].Get(),
			nullptr,
			output.myRTVs[idx].GetAddressOf());
		//assert(SUCCEEDED(result));
		result = ge->GetDevice()->CreateShaderResourceView(
			output.myTextures[idx].Get(),
			nullptr,
			output.mySRVs[idx].GetAddressOf());
		//assert(SUCCEEDED(result));
	}

	output.myViewport = std::make_shared<D3D11_VIEWPORT>(
		D3D11_VIEWPORT{
		0,
		0,
		static_cast<float>(desc.Width),
		static_cast<float>(desc.Height),
		0,
		1
		});

	return output;
}

void GBuffer::ClearTextures()
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	Vector4f clearColor = { 0,0,0,0 };
	for (unsigned int idx = 0; idx < (int)GBufferTexture::Count; idx++)
	{
		ge->GetContext()->ClearRenderTargetView(myRTVs[idx].Get(), &clearColor.x);
	}
}

void GBuffer::SetAsActiveTarget(DepthBuffer* aDepth)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ID3D11RenderTargetView* nullRTV[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };
	ge->GetContext()->OMSetRenderTargets(5, nullRTV, nullptr);
	ID3D11ShaderResourceView* nullSRVs[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
	ge->GetContext()->PSSetShaderResources(0, (int)GBufferTexture::Count, nullSRVs);

	if (aDepth)
	{
		ge->GetContext()->OMSetRenderTargets((int)GBufferTexture::Count, myRTVs[0].GetAddressOf(), aDepth->GetDSV());
	}
	else
	{
		ge->GetContext()->OMSetRenderTargets((int)GBufferTexture::Count, myRTVs[0].GetAddressOf(), nullptr);
	}
	ge->GetContext()->RSSetViewports(1, myViewport.get());
}

void GBuffer::SetAsTarget(GBufferTexture atexture)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ge->GetContext()->OMSetRenderTargets(1, myRTVs[(int)atexture].GetAddressOf(), nullptr);
	ge->GetContext()->RSSetViewports(1, myViewport.get());
}

void GBuffer::SetAsResourceOnSlot(GBufferTexture atexture, unsigned aSlot)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ge->GetContext()->PSSetShaderResources(aSlot, 1, mySRVs[(int)atexture].GetAddressOf());
}

void GBuffer::SetAllAsResources(unsigned aSlot)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ID3D11ShaderResourceView* nullSRVs[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
	ge->GetContext()->PSSetShaderResources(aSlot, (int)GBufferTexture::Count, nullSRVs);

	ge->GetContext()->PSSetShaderResources(aSlot, (int)GBufferTexture::Count, mySRVs[0].GetAddressOf());
}

void GBuffer::Unbind()
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ID3D11RenderTargetView* nullRTV[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };
	ge->GetContext()->OMSetRenderTargets(5, nullRTV, nullptr);
	ID3D11ShaderResourceView* nullSRVs[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
	ge->GetContext()->PSSetShaderResources(0, (int)GBufferTexture::Count, nullSRVs);
}

void GBuffer::Cleanup()
{
	for (unsigned int idx = 0; idx < (int)GBufferTexture::Count; idx++)
	{
		myRTVs[idx]->Release();
		mySRVs[idx]->Release();
		myTextures[idx]->Release();
	}
}

ComPtr<ID3D11ShaderResourceView> GBuffer::GetSRV(GBufferTexture aTexture)
{
	return mySRVs[(int)aTexture];
}