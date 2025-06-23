#include "Texture2D.h"

#include <d3d11.h>
#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

namespace Zengine
{
#pragma region [CONSTRUCTOR]
	Texture2D::Texture2D(const unsigned& _width, const unsigned& _height, const TextureFormat& _format)
		: Texture(), width(_width), height(_height), format(_format)
	{
		pixelData.resize(height * width * 4, 255);
	}

	Texture2D::Texture2D(const unsigned& _width, const unsigned& _height,
		std::vector<unsigned char>& _defaultData, const TextureFormat& _format)
		: Texture(), width(_width), height(_height), format(_format)
	{
		pixelData.insert(pixelData.begin(), _defaultData.begin(), _defaultData.end());
	}

	Texture2D::Texture2D() : Texture(), width(0), height(0), format((TextureFormat)0) {}
	Texture2D::Texture2D(const size_t& _id) : Texture(_id), width(0), height(0), format((TextureFormat)0) {	}
#pragma endregion

	const ID3D11Texture2D* Texture2D::GetTexture() const { return texture; }
	ID3D11Texture2D* Texture2D::GetTexture() { return texture; }
	ID3D11Texture2D** Texture2D::GetTextureAddr() { return &texture; }

	const std::vector<unsigned char>& Texture2D::GetData() const { return pixelData; }
	std::vector<unsigned char>& Texture2D::GetData() { return pixelData; }

	void Texture2D::SetData(std::vector<unsigned char>& data) { pixelData = data; }

	void Texture2D::CreateTexture()
	{
		static D3D11_TEXTURE2D_DESC desc = { };
		{
			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 0;
			desc.ArraySize = 1;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
		}

		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();


		HRESULT hr = ge->GetDevice()->CreateTexture2D(&desc, nullptr, &texture);
		if (FAILED(hr))
		{
			texture->Release();
			return;
		}

		hr = ge->GetDevice()->CreateShaderResourceView(texture, 0, &srv);
		if (FAILED(hr))
		{
			srv->Release();
			return;
		}

		ge->GetContext()->UpdateSubresource(texture, 0, nullptr, (void*)pixelData.data(),
			width * 4, width * height * 4);
		ge->GetContext()->GenerateMips(srv);
	}
}

