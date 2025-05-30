#include "TextureImporter.h"

#include <Engine/AssetManagement/Assets/Texture.h>
#include <unordered_map>
#include <Engine/AssetManagement/AssetsCommon.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <External/stb_image/stb_image.h>
#include <External/DDSTextureLoader/DDSTextureLoader11.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>
#include <fstream>

enum class Importers
{
	STBI, DDS_IMPORTER
};



void TextureImporter::Load(const size_t& aID, Texture& aOutAsset)
{
	std::ifstream in(ZENGINE_ASSETS_PATH "textures.bundle", std::ios::binary);
	BinaryExporter::AssetHeader header;
	in.read(reinterpret_cast<char*>(&header), sizeof(BinaryExporter::AssetHeader));

	BinaryExporter::TextureIndex index{};
	bool found = false;
	for (int i = 0; i < header.totalAmount; i++)
	{
		in.read(reinterpret_cast<char*>(&index), sizeof(BinaryExporter::TextureIndex));
		if (index.id == aID)
		{
			found = true;
			break;
		}
	}

	if (!found) return;

	in.seekg(index.offset);

	std::string data;
	data.resize(index.size);

	in.read(data.data(), index.size);



	D3D11_TEXTURE2D_DESC desc = { };
	{
		desc.Width = index.width;
		desc.Height = index.height;
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


	HRESULT hr = ge->GetDevice()->CreateTexture2D(&desc, nullptr, aOutAsset.GetTextureAddress());
	if (FAILED(hr))
	{
		aOutAsset.GetTexture()->Release();
		return;
	}

	hr = ge->GetDevice()->CreateShaderResourceView(aOutAsset.GetTexture(), 0, aOutAsset.GetShaderResourceAddress());
	if (FAILED(hr))
	{
		aOutAsset.GetShaderResource()->Release();
		return;
	}

	ge->GetContext()->UpdateSubresource(aOutAsset.GetTexture(), 0, nullptr, (void*)data.data(), 
		index.width * 4, index.width * index.height * 4);
	ge->GetContext()->GenerateMips(aOutAsset.GetShaderResource());
}

void TextureImporter::Load(const char* aPath, Texture& aOutAsset)
{
	static std::unordered_map<std::string, Importers> supportedTextureTypes = {
	{".png" , Importers::STBI}          ,
	{".jpg" , Importers::STBI}          ,
	{".jpeg", Importers::STBI}          ,
	{".bmp" , Importers::STBI}          ,
	{".tga" , Importers::STBI}          ,
	{".gif" , Importers::STBI}          ,
	{".psd" , Importers::STBI}          ,
	{".hdr" , Importers::STBI}          ,
	{ ".dds" , Importers::DDS_IMPORTER },
	};

	Importers importer = supportedTextureTypes[std::filesystem::path(aPath).extension().string()];

	switch (importer)
	{
	case Importers::DDS_IMPORTER: Load_DDS(aPath, aOutAsset); break;
	case Importers::STBI: Load_STBI(aPath, aOutAsset); break;

	default: DebugLogger::LogWarning("Not supported format."); break;
	}
}

void TextureImporter::Unload(Texture& aOutAsset)
{
	aOutAsset.GetTexture()->Release();
	aOutAsset.GetShaderResource()->Release();
}


void TextureImporter::Load_STBI(const char* aPath, Texture& aOutAsset)
{
	int width, height, channels;
	unsigned char* img = stbi_load(aPath, &width, &height, &channels, 0);

	std::vector<unsigned char> image;
	if (channels == 1)
	{
		ConvertToGreyScale(img, width, height, image);
	}
	else if (channels == 3)
	{
		ConvertToRGBA(img, width, height, image);
	}
	else if (channels == 4)
	{
		image.assign(img, img + (width * height * 4));
	}
	else
	{
		DebugLogger::LogError("Unsupported amount of channels.");
		stbi_image_free(img);

		return;
	}

	stbi_image_free(img);

	D3D11_TEXTURE2D_DESC desc = { };
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


	HRESULT hr = ge->GetDevice()->CreateTexture2D(&desc, nullptr, aOutAsset.GetTextureAddress());
	if (FAILED(hr))
	{
		aOutAsset.GetTexture()->Release();
		return;
	}

	hr = ge->GetDevice()->CreateShaderResourceView(aOutAsset.GetTexture(), 0, aOutAsset.GetShaderResourceAddress());
	if (FAILED(hr))
	{
		aOutAsset.GetShaderResource()->Release();
		return;
	}

	ge->GetContext()->UpdateSubresource(aOutAsset.GetTexture(), 0, nullptr, (void*)image.data(), width * 4, width * height * 4);
	ge->GetContext()->GenerateMips(aOutAsset.GetShaderResource());
}

void TextureImporter::Load_DDS(const char* aPath, Texture& aOutAsset)
{
	const std::string path = aPath;
	const std::wstring wPath = std::wstring(path.begin(), path.end());

	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		ge->GetDevice(), 
		wPath.c_str(), 
		0,
		D3D11_USAGE_DEFAULT, 
		D3D11_BIND_SHADER_RESOURCE, 
		0, 
		0, 
		true, 
		(ID3D11Resource**)aOutAsset.GetTextureAddress(), 
		aOutAsset.GetShaderResourceAddress());

	if (FAILED(hr))
	{
		aOutAsset.GetTexture()->Release();
		aOutAsset.GetShaderResource()->Release();
	}
}

void TextureImporter::ConvertToRGBA(const unsigned char* someData, const int& aWidth, 
	const int& aHeight, std::vector<unsigned char>& aOutDst)
{
	aOutDst.resize(aWidth * aHeight * 4);
	for (int i = 0; i < aWidth * aHeight; i++)
	{
		aOutDst[4 * i + 0] = someData[3 * i + 0];
		aOutDst[4 * i + 1] = someData[3 * i + 1];
		aOutDst[4 * i + 2] = someData[3 * i + 2];
		aOutDst[4 * i + 3] = 255;
	}
}

void TextureImporter::ConvertToGreyScale(const unsigned char* someData, const int& aWidth, const int& aHeight, std::vector<unsigned char>& aOutDst)
{
	aOutDst.resize(aWidth * aHeight * 4);
	for (int i = 0; i < aWidth * aHeight; i++)
	{
		unsigned char gray = someData[i];
		aOutDst[4 * i + 0] = gray;
		aOutDst[4 * i + 1] = gray;
		aOutDst[4 * i + 2] = gray;
		aOutDst[4 * i + 3] = 255;
	}
}
