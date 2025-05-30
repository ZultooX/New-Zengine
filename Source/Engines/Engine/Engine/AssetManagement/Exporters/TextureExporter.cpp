#include "TextureExporter.h"

#include <External/DDSTextureLoader/DDSTextureLoader11.h>
#include <External/stb_image/stb_image.h>

#include <Engine/AssetManagement/AssetsCommon.hpp>
#include <Engine/AssetManagement/Assets/Texture.h>

#include <filesystem>
#include <fstream>

void TextureExporter::ExportToBinaryFile(const char* aOutDst, const Texture& aVertexShader)
{
	
}

void TextureExporter::ExportAllToBinaryFile(const char* aOutDst)
{
	{ // write to binary file
		std::vector<std::string> textures;
		std::vector<BinaryExporter::TextureIndex> myIndex;
		for (const auto& entry : std::filesystem::directory_iterator(ZENGINE_TEXTURES_PATH))
		{
			int width, height, channels;
			unsigned char* img = stbi_load(entry.path().string().c_str(),
				&width, &height, &channels, 0);

			if (img == nullptr) continue;

			BinaryExporter::TextureIndex texIndex;
			texIndex.channels = channels;
			texIndex.height = height;
			texIndex.width = width;
			texIndex.size = width * height * channels;


			myIndex.push_back(texIndex);

			std::string textureData;
			textureData.reserve(width * height * channels);

			textureData.assign(reinterpret_cast<char*>(img), width * height * channels);

			textures.push_back(std::move(textureData));

			stbi_image_free(img);
		}


		std::ofstream out(ZENGINE_ASSETS_PATH"textures.bundle", std::ios::binary);
		BinaryExporter::AssetHeader header = { textures.size() };
		out.write(reinterpret_cast<char*>(&header), sizeof(BinaryExporter::AssetHeader));

		int currentOffset = sizeof(BinaryExporter::AssetHeader) + myIndex.size() * sizeof(BinaryExporter::TextureIndex);

		for (int i = 0; i < (int)textures.size(); i++)
		{
			if (i == 0)
			{
				myIndex[i].offset = sizeof(BinaryExporter::AssetHeader) + sizeof(BinaryExporter::TextureIndex) * myIndex.size();
			}
			else
			{
				myIndex[i].offset = myIndex[i - 1].offset + myIndex[i - 1].size;
			}
		}

		for (auto& meta : myIndex)
		{
			out.write(reinterpret_cast<char*>(&meta), sizeof(BinaryExporter::TextureIndex));
		}

		for (const auto& tex : textures)
		{
			out.write(reinterpret_cast<const char*>(tex.data()), tex.size());
		}
	}	
}
