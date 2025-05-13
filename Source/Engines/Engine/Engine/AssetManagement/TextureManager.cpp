#include "TextureManager.h"

#include <unordered_map>
#include <string>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <External/DDSTextureLoader/DDSTextureLoader11.h>
#include <External/stb_image/stb_image.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

enum class TextureTypes
{
	JPEG,
	PNG,
	TGA,
	BMP,
	PSD,
	GIF,
	HDR,
	PIC,
	PNM,
	DDS
};

static const std::unordered_map<std::string, TextureTypes> ExtensionToType = {
	std::pair<std::string, TextureTypes>(".jpeg", TextureTypes::JPEG),
	std::pair<std::string, TextureTypes>(".png", TextureTypes::PNG),
	std::pair<std::string, TextureTypes>(".tga", TextureTypes::TGA),
	std::pair<std::string, TextureTypes>(".bmp", TextureTypes::BMP),
	std::pair<std::string, TextureTypes>(".psd", TextureTypes::PSD),
	std::pair<std::string, TextureTypes>(".gif", TextureTypes::GIF),
	std::pair<std::string, TextureTypes>(".hdr", TextureTypes::HDR),
	std::pair<std::string, TextureTypes>(".pic", TextureTypes::PIC),
	std::pair<std::string, TextureTypes>(".pnm", TextureTypes::PNM),

	std::pair<std::string, TextureTypes>(".dds", TextureTypes::DDS),
};

Texture* TextureManager::Load(const std::string& aTexturePath)
{
	if (!std::filesystem::exists(aTexturePath)) return Get(ZENGINE_TEXTURES_PATH"Error.png");

	TextureTypes type = ExtensionToType.at(std::filesystem::path(aTexturePath).extension().string());
	switch (type)
	{
	case TextureTypes::JPEG:
	case TextureTypes::PNG:
	case TextureTypes::TGA:
	case TextureTypes::BMP:
	case TextureTypes::PSD:
	case TextureTypes::GIF:
	case TextureTypes::HDR:
	case TextureTypes::PIC:
	case TextureTypes::PNM:
	{
		return LoadSTB(aTexturePath);
	}

	case TextureTypes::DDS:
	{
		return LoadDDS(aTexturePath);
	}

	default:
		return Get(ZENGINE_TEXTURES_PATH"Error.png");
	}
}

Texture* TextureManager::GetDefaultNormal() { return Get(myDefaultNormalPath); }

Texture* TextureManager::LoadDDS(const std::string& aTexturePath)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();


	myPathToIdx[aTexturePath] = myAssets.size();

	myAssets.emplace_back(new Texture());

	std::wstring path = std::wstring(aTexturePath.begin(), aTexturePath.end());

	DirectX::CreateDDSTextureFromFileEx(
		ge->GetDevice(),
		path.c_str(),
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		true,
		nullptr,
		myAssets.back()->GetSRVAddress());

	return myAssets.back();
}

Texture* TextureManager::LoadSTB(const std::string& aTexturePath)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();


	myPathToIdx[aTexturePath] = myAssets.size();

	myAssets.emplace_back(new Texture());




	std::vector<unsigned char> rgbaPixels;
	int width, height, channels;
	unsigned char* img = stbi_load(aTexturePath.c_str(), &width, &height, &channels, 0);

	if (img == nullptr)
		assert(false && "No wookie");


	if (channels == 1)  // Convert Grayscale to RGBA
	{
		rgbaPixels.resize(width * height * 4);
		for (int i = 0; i < width * height; i++)
		{
			unsigned char gray = img[i];  // Single grayscale value
			rgbaPixels[4 * i + 0] = gray; // R
			rgbaPixels[4 * i + 1] = gray; // G
			rgbaPixels[4 * i + 2] = gray; // B
			rgbaPixels[4 * i + 3] = 255;  // Alpha (fully opaque)
		}
	}
	else if (channels == 3)  // Convert RGB to RGBA
	{
		rgbaPixels.resize(width * height * 4);
		for (int i = 0; i < width * height; i++)
		{
			rgbaPixels[4 * i + 0] = img[3 * i + 0];
			rgbaPixels[4 * i + 1] = img[3 * i + 1];
			rgbaPixels[4 * i + 2] = img[3 * i + 2];
			rgbaPixels[4 * i + 3] = 255;  // Alpha channel set to 255
		}
	}
	else if (channels == 4)  // Already RGBA, just copy
	{
		rgbaPixels.assign(img, img + (width * height * 4));
	}




	ID3D11Texture2D* texture = nullptr;

	D3D11_TEXTURE2D_DESC desc = { };
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 0;
	desc.ArraySize = 1;

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.Usage = D3D11_USAGE_DEFAULT;


	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;


	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;


	HRESULT hr = ge->GetDevice()->CreateTexture2D(&desc, nullptr, &texture);
	if (FAILED(hr))
	{
		texture->Release();
	}

	hr = ge->GetDevice()->CreateShaderResourceView(texture, NULL, myAssets.back()->GetSRVAddress());
	if (FAILED(hr))
	{
		texture->Release();
	}

	ge->GetContext()->UpdateSubresource(texture, 0, nullptr, (void*)rgbaPixels.data(), width * 4, width * height * 4);
	ge->GetContext()->GenerateMips(myAssets.back()->GetSRV());

	return myAssets.back();
}
