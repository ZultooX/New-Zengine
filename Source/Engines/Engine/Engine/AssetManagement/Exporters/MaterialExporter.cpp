#include "MaterialExporter.h"

#include <Engine/AssetManagement/Assets/Material.h>
#include <Engine/AssetManagement/Assets/VertexShader.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Assets/Texture.h>
#include <External/nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <Engine/AssetManagement/JsonUtils.h>

#include <Engine/AssetManagement/Importers/MaterialImporter.h>
#include <Engine/AssetManagement/AssetsCommon.hpp>

void MaterialExporter::CreateNewMaterialFile(const char* aOutDst, const Material& aMaterial)
{
	using namespace nlohmann;

	ordered_json  json;

	for (const TextureData& texture : aMaterial.GetTextures())
	{
		json[Json::TexturesKey].push_back({ texture.name, texture.texture.Get()->GetPath(), texture.bindPoint });
	}

	if (aMaterial.GetVertexShader().Get())
	{
		json[Json::VertexShaderKey] = aMaterial.GetVertexShader().Get()->GetPath();
	}
	else
	{
		json[Json::VertexShaderKey] = Json::VertexShaderDefault;
	}

	if (aMaterial.GetPixelShader().Get())
	{
		json[Json::PixelShaderKey] = aMaterial.GetPixelShader().Get()->GetPath();
	}
	else
	{
		json[Json::PixelShaderKey] = Json::PixelShaderDefault;
	}

	json[Json::Color::Key] =
	{
		{Json::Color::R, aMaterial.GetMaterialData().MB_albedoColor.r},
		{Json::Color::G, aMaterial.GetMaterialData().MB_albedoColor.g},
		{Json::Color::B, aMaterial.GetMaterialData().MB_albedoColor.b},
		{Json::Color::A, aMaterial.GetMaterialData().MB_albedoColor.a},
	};

	std::fstream file(aOutDst);
	if (!file.is_open()) return;

	file << json.dump(4);

	file.close();
}

void MaterialExporter::ExportToBinaryFile(const char* aOutDst, const Material& aMaterial)
{
}

void MaterialExporter::ExportAllToBinaryFile(const char* aOutDst)
{
	std::vector<BinaryExporter::MaterialData> myBinaryData;
	std::vector<BinaryExporter::AssetIndex> myIndex;

	for (const auto& entry : std::filesystem::directory_iterator(ZENGINE_MATERIALS_PATH))
	{
		Material material = Material(entry.path().string().c_str());



		BinaryExporter::MaterialData data;
		data.data = material.GetMaterialData();
		data.pixelShaderID = material.GetPixelShader()->GetID();
		data.vertexShaderID = material.GetVertexShader()->GetID();


		for (const TextureData& texture : material.GetTextures())
		{
			BinaryExporter::MaterialData::Texture tex;
			tex.bindPoint = texture.bindPoint;
			tex.textureID = texture.texture->GetID();
			data.textures.push_back(tex);
		}

		BinaryExporter::AssetIndex index;
		index.id = material.GetID();

		int textureAmount = (int)data.textures.size();
		index.size = sizeof(MaterialBufferData) + sizeof(size_t) * 2 + sizeof(int);
		index.size += data.textures.size() * sizeof(BinaryExporter::MaterialData::Texture);

		myBinaryData.push_back(std::move(data));
		myIndex.push_back(std::move(index));
	}

	for (int i = 0; i < (int)myBinaryData.size(); i++)
	{
		if (i == 0)
		{
			myIndex[i].offset = sizeof(BinaryExporter::AssetHeader) + sizeof(BinaryExporter::AssetIndex) * myIndex.size();
		}
		else
		{
			myIndex[i].offset = myIndex[i - 1].offset + myIndex[i - 1].size;
		}
	}


	std::ofstream out(aOutDst, std::ios::binary);
	if (!out.is_open()) return;

	BinaryExporter::AssetHeader header;
	header.totalAmount = static_cast<int>(myBinaryData.size());
	out.write(reinterpret_cast<const char*>(&header), sizeof(header));

	for (const BinaryExporter::AssetIndex& idx : myIndex)
	{
		out.write(reinterpret_cast<const char*>(&idx), sizeof(BinaryExporter::AssetIndex));
	}

	int currentOffset = (int)(sizeof(BinaryExporter::AssetHeader) + (sizeof(BinaryExporter::AssetIndex) * myIndex.size()));
	for (const BinaryExporter::MaterialData& data : myBinaryData)
	{
		out.write(reinterpret_cast<const char*>(&data.data), sizeof(MaterialBufferData));

		int textureAmount = data.textures.size();
		out.write(reinterpret_cast<const char*>(&textureAmount), sizeof(int));
		for (const BinaryExporter::MaterialData::Texture& tex : data.textures)
		{
			out.write(reinterpret_cast<const char*>(&tex), sizeof(BinaryExporter::MaterialData::Texture));
		}

		out.write(reinterpret_cast<const char*>(&data.pixelShaderID), sizeof(size_t));
		out.write(reinterpret_cast<const char*>(&data.vertexShaderID), sizeof(size_t));
	}
}
