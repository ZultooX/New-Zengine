#include "MaterialImporter.h"

#include <Engine/AssetManagement/Assets/Material.h>
#include <Engine/AssetManagement/Assets/VertexShader.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <External/nlohmann/json.hpp>
#include <fstream>
#include <Engine/AssetManagement/AssetsCommon.hpp>

#include <Engine/AssetManagement/JsonUtils.h>

std::vector<BinaryExporter::AssetIndex> MaterialImporter::myLoadedMeshes;


void MaterialImporter::Load(const size_t& aID, Material& aOutAsset)
{
	std::ifstream in(ZENGINE_ASSETS_PATH "materials.bundle", std::ios::binary);
	BinaryExporter::AssetHeader header;
	in.read(reinterpret_cast<char*>(&header), sizeof(BinaryExporter::AssetHeader));

	BinaryExporter::AssetIndex index{};
	bool found = false;
	for (int i = 0; i < header.totalAmount; i++)
	{
		in.read(reinterpret_cast<char*>(&index), sizeof(BinaryExporter::AssetIndex));
		if (index.id == aID)
		{
			found = true;
			break;
		}
	}

	if (!found) return;

	in.seekg(index.offset);

	BinaryExporter::MaterialData data;

	in.read(reinterpret_cast<char*>(&data.data), sizeof(MaterialBufferData));

	int textureCount = 0;
	in.read(reinterpret_cast<char*>(&textureCount), sizeof(int));

	data.textures.resize(textureCount);
	in.read(reinterpret_cast<char*>(data.textures.data()), textureCount * sizeof(BinaryExporter::MaterialData::Texture));

	in.read(reinterpret_cast<char*>(&data.pixelShaderID), sizeof(size_t));
	in.read(reinterpret_cast<char*>(&data.vertexShaderID), sizeof(size_t));

	aOutAsset.SetMaterialData(data.data);
	aOutAsset.myPS = AssetManager::GetFromID<PixelShader>(data.pixelShaderID);
	aOutAsset.myVS = AssetManager::GetFromID<VertexShader>(data.vertexShaderID);

	for (const BinaryExporter::MaterialData::Texture& tex : data.textures)
	{
		TextureData t;
		t.bindPoint = tex.bindPoint;
		t.texture = AssetManager::GetFromID<Texture>(tex.textureID);
		aOutAsset.myTextures.push_back(std::move(t));
	}
}

void MaterialImporter::Load(const char* aPath, Material& aOutAsset)
{
	using namespace nlohmann;

	std::ifstream file(aPath);
	json jsonFile;
	jsonFile << file;

	Zengine::Util::BitMask<> bit;
	for (json& element : jsonFile[Json::TexturesKey])
	{
		aOutAsset.myTextures.push_back({});
		aOutAsset.myTextures.back().name = element[0];

		std::string path = element[1];
		aOutAsset.myTextures.back().texture = AssetManager::GetFromPath<Texture>(path.c_str());
		aOutAsset.myTextures.back().bindPoint = element[2];

		bit.SetBit(aOutAsset.myTextures.back().bindPoint, true);
	}

	aOutAsset.GetMaterialData().MB_textureIsSetFlag = bit.GetMask();

	std::string vsPath = jsonFile.value(Json::VertexShaderKey, Json::VertexShaderDefault).c_str();
	std::string psPath = jsonFile.value(Json::PixelShaderKey, Json::PixelShaderDefault).c_str();
	aOutAsset.myVS = AssetManager::GetFromPath<VertexShader>(vsPath.c_str());
	aOutAsset.myPS = AssetManager::GetFromPath<PixelShader>(psPath.c_str());


	if (jsonFile.contains(Json::Color::Key))
	{
		const json& color = jsonFile[Json::Color::Key];

		aOutAsset.GetMaterialData().MB_albedoColor.r = color.value(Json::Color::R, Json::Color::DefaultR);
		aOutAsset.GetMaterialData().MB_albedoColor.g = color.value(Json::Color::G, Json::Color::DefaultG);
		aOutAsset.GetMaterialData().MB_albedoColor.b = color.value(Json::Color::B, Json::Color::DefaultB);
		aOutAsset.GetMaterialData().MB_albedoColor.a = color.value(Json::Color::A, Json::Color::DefaultA);
	}
}

void MaterialImporter::Unload(Material& aOutAsset)
{
}

void MaterialImporter::LoadmportedAssets()
{
	std::ifstream in(ZENGINE_ASSETS_PATH "materials.bundle", std::ios::binary);
	BinaryExporter::AssetHeader header;
	in.read(reinterpret_cast<char*>(&header), sizeof(BinaryExporter::AssetHeader));

	BinaryExporter::AssetIndex index{};
	bool found = false;
	for (int i = 0; i < header.totalAmount; i++)
	{
		in.read(reinterpret_cast<char*>(&index), sizeof(BinaryExporter::AssetIndex));
		myLoadedMeshes.push_back(index);
	}
}

std::vector<BinaryExporter::AssetIndex>& MaterialImporter::GetImportedAssets()
{
	return myLoadedMeshes;
}
