#include "MaterialLoader.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include <Engine/Objects/Base/JsonUtils.h>
#include <Engine/Objects/AssetManagement/Base/AssetManager.hpp>
#include <Engine/Objects/Base/AssetsCommon.hpp>
#include <Engine/Utilities/MainSingleton.h>

namespace Zengine
{
	void MaterialLoader::Load(const char* path, MaterialData& materialData)
	{
		using namespace nlohmann;

		std::ifstream file(path);
		json jsonFile;
		jsonFile << file;

		AssetManager& assetManager = MainSingleton::GetInstance<AssetManager>();
		Zengine::Util::BitMask<> bit;
		for (json& element : jsonFile[Json::TexturesKey])
		{
			const size_t textureId = std::hash<std::string>{}(element[1]);
			const unsigned bindSlot = element[2];

			materialData.textureIds.push_back(textureId);
			materialData.textureBindSlots.push_back(bindSlot);

			bit.SetBit(bindSlot, true);
		}

		materialData.textureIsSetFlag = bit.GetMask();

		materialData.vsId = jsonFile.value(Json::VertexShaderKey, 0);
		materialData.psId = jsonFile.value(Json::PixelShaderKey, 0);
		materialData.id = std::hash<std::string>{}(path);

		materialData.roughness = jsonFile.value(Json::RoughnessKey, Json::RoughnessDefault);
		materialData.metallic = jsonFile.value(Json::MetallicKey, Json::MetallicDefault);
		materialData.aOStrength = jsonFile.value(Json::AOStrengthKey, Json::AOStrengthDefault);
		materialData.bloomIntensity = jsonFile.value(Json::BloomIntensityKey, Json::BloomIntensityDefault);
		materialData.normalStrength = jsonFile.value(Json::NormalStrengthKey, Json::NormalStrengthDefault);


		if (jsonFile.contains(Json::Color::Key))
		{
			const json& color = jsonFile[Json::Color::Key];

			materialData.albedoTint.r = color.value(Json::Color::R, Json::Color::DefaultR);
			materialData.albedoTint.g = color.value(Json::Color::G, Json::Color::DefaultG);
			materialData.albedoTint.b = color.value(Json::Color::B, Json::Color::DefaultB);
			materialData.albedoTint.a = color.value(Json::Color::A, Json::Color::DefaultA);
		}
	}

	void MaterialLoader::Load(const size_t& id, Material& material)
	{
		std::ifstream in("Materials.bundle", std::ios::binary);
		if (!in.is_open()) return;

		BinaryExporter::AssetHeader header;
		in.read(reinterpret_cast<char*>(&header), sizeof(BinaryExporter::AssetHeader));

		bool found = false;
		BinaryExporter::AssetIndex index;
		for (int i = 0; i < header.totalAmount; ++i)
		{
			in.read(reinterpret_cast<char*>(&index), sizeof(BinaryExporter::AssetIndex));
			if (index.id == id)
			{
				found = true;
				break;
			}
		}

		if (!found) return;

		in.seekg(index.offset);

		Color albedoTint;
		float roughness = 0, metallic = 0, aoStrength = 0, bloomIntensity = 0;
		int textureSetFlag = 0;
		size_t vsId = 0, psId = 0;

		in.read(reinterpret_cast<char*>(&albedoTint), sizeof(Color));
		in.read(reinterpret_cast<char*>(&roughness), sizeof(float));
		in.read(reinterpret_cast<char*>(&metallic), sizeof(float));
		in.read(reinterpret_cast<char*>(&aoStrength), sizeof(float));
		in.read(reinterpret_cast<char*>(&bloomIntensity), sizeof(float));
		in.read(reinterpret_cast<char*>(&textureSetFlag), sizeof(int));
		in.read(reinterpret_cast<char*>(&vsId), sizeof(size_t));
		in.read(reinterpret_cast<char*>(&psId), sizeof(size_t));

		int textureAmount = 0;
		in.read(reinterpret_cast<char*>(&textureAmount), sizeof(int));
		for (int i = 0; i < textureAmount; ++i)
		{
			size_t textureId = 0;
			unsigned bindSlot = 0;

			in.read(reinterpret_cast<char*>(&textureId), sizeof(size_t));
			in.read(reinterpret_cast<char*>(&bindSlot), sizeof(unsigned));
		}



		material.SetID(index.id);
		material.SetColor(albedoTint);
		material.SetRoughness(roughness);
		material.SetMetallic(metallic);
		material.SetAoStrength(aoStrength);
		material.SetBloomIntensity(bloomIntensity);
		material.SetTextureSetFlags(textureSetFlag);

		//AssetManager& assetManager = MainSingleton::GetInstance<AssetManager>();
		//material.myVS = assetManager.Get<VertexShader>(vsId);
		//material.myPS = assetManager.Get<PixelShader>(psId);
	}

	void MaterialLoader::ExportMaterials()
	{
		using namespace BinaryExporter;

		std::vector<MaterialData> materialList;

		for (const auto& entry : std::filesystem::directory_iterator(ZENGINE_ASSETS_PATH))
		{
			const std::string extension = entry.path().stem().string();

			if (extension == ".mat")
			{
				materialList.push_back({});
				MaterialData& data = materialList.back();
				Load(entry.path().string().c_str(), data);
			}
		}

		AssetHeader header;
		header.totalAmount = (int)materialList.size();

		std::vector<AssetIndex> indexList;
		for (const MaterialData& data : materialList)
		{
			indexList.push_back({});
			AssetIndex& index = indexList.back();

			index.id = data.id;
			index.size =
				sizeof(float) * 9 +
				sizeof(int) +
				sizeof(size_t) * 3 +
				sizeof(size_t) * data.textureIds.size() +
				sizeof(unsigned) * data.textureBindSlots.size();
		}

		for (int i = 0; i < (int)indexList.size(); i++)
		{
			if (i == 0)
			{
				indexList[i].offset = sizeof(BinaryExporter::AssetHeader) + sizeof(BinaryExporter::AssetIndex) * indexList.size();
			}
			else
			{
				indexList[i].offset = indexList[i - 1].offset + indexList[i - 1].size;
			}
		}

		std::ofstream out("Materials.bundle", std::ios::binary);
		if (!out.is_open()) return;

		out.write(reinterpret_cast<const char*>(&header), sizeof(BinaryExporter::AssetHeader));

		for (const BinaryExporter::AssetIndex& idx : indexList)
		{
			out.write(reinterpret_cast<const char*>(&idx), sizeof(BinaryExporter::AssetIndex));
		}

		int currentOffset = (int)(sizeof(BinaryExporter::AssetHeader) + (sizeof(BinaryExporter::AssetIndex) * indexList.size()));
		for (const MaterialData& data : materialList)
		{
			out.write(reinterpret_cast<const char*>(&data.albedoTint), sizeof(Color));
			out.write(reinterpret_cast<const char*>(&data.roughness), sizeof(float));
			out.write(reinterpret_cast<const char*>(&data.metallic), sizeof(float));
			out.write(reinterpret_cast<const char*>(&data.aOStrength), sizeof(float));
			out.write(reinterpret_cast<const char*>(&data.bloomIntensity), sizeof(float));
			out.write(reinterpret_cast<const char*>(&data.textureIsSetFlag), sizeof(int));
			out.write(reinterpret_cast<const char*>(&data.vsId), sizeof(size_t));
			out.write(reinterpret_cast<const char*>(&data.psId), sizeof(size_t));

			const int textureAmount = (int)data.textureIds.size();
			out.write(reinterpret_cast<const char*>(&textureAmount), sizeof(int));
			for (int i = 0; i < textureAmount; ++i)
			{
				const size_t& textureId = data.textureIds[i];
				const unsigned& bindSlot = data.textureBindSlots[i];

				out.write(reinterpret_cast<const char*>(&textureId), sizeof(size_t));
				out.write(reinterpret_cast<const char*>(&bindSlot), sizeof(unsigned));
			}
		}
	}
}