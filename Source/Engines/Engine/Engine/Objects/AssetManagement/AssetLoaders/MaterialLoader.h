#pragma once

#include <Engine/Objects/AssetManagement/Assets/Material.h>

namespace Zengine
{
	struct MaterialData
	{
		Color albedoTint;

		float roughness = 0;
		float metallic = 0;
		float aOStrength = 0;
		float bloomIntensity = 0;

		float normalStrength = 0;

		std::vector<size_t> textureIds;
		std::vector<unsigned> textureBindSlots;
		int textureIsSetFlag = 0;

		size_t vsId;
		size_t psId;
		size_t id;
	};

	class MaterialLoader
	{
	public:
		static void Load(const char* path, MaterialData& materialData);
		static void Load(const size_t& id, Material& material);


	public:
		static void ExportMaterials();
	};
}