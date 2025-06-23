#include "Texture2DLoader.h"

#include <unordered_map>
#include <filesystem>
#include <stb_image/stb_image.h>
#include <DDSTextureLoader/DDSTextureLoader11.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

namespace Zengine
{
	enum class Importers
	{
		STBI, DDS_IMPORTER
	};

	void Texture2DLoader::Load(const char* path, Texture2D& texture)
	{
		static std::unordered_map<const char*, Importers> supportedTextureTypes = {
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

		Importers importer = supportedTextureTypes[std::filesystem::path(path).extension().string().c_str()];

		switch (importer)
		{
		case Importers::DDS_IMPORTER: Load_DDS(path, texture); break;
		case Importers::STBI: Load_STBI(path, texture); break;
		}

		texture.SetFlag(0, true);
		texture.SetPath(path);
	}

	void Texture2DLoader::Load_STBI(const char* path, Texture2D& texture)
	{
		int width, height, channels;
		unsigned char* img = stbi_load(path, &width, &height, &channels, 0);

		if (channels == 1)
		{
			ConvertToGreyScale(img, width, height, texture.GetData());
		}
		else if (channels == 3)
		{
			ConvertToRGBA(img, width, height, texture.GetData());
		}
		else if (channels == 4)
		{
			texture.GetData().assign(img, img + (width * height * 4));
		}
		else
		{
			stbi_image_free(img);
			return;
		}

		stbi_image_free(img);

		texture.CreateTexture();
	}

	void Texture2DLoader::Load_DDS(const char* path, Texture2D& texture)
	{
		const std::string _path = path;
		const std::wstring wPath = std::wstring(_path.begin(), _path.end());

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
			(ID3D11Resource**)texture.GetTextureAddr(),
			texture.GetSRVAddr());

		if (FAILED(hr))
		{
			texture.GetTexture()->Release();
			texture.GetSRV()->Release();
		}
	}
}
