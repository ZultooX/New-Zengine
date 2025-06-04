#pragma once

#include <Engine/AssetManagement/AssetsCommon.hpp>

class Material;
class MaterialImporter
{
public:
	static void Load(const size_t& aID, Material& aOutAsset);
	static void Load(const char* aPath, Material& aOutAsset);
	static void Unload(Material& aOutAsset);

	static void LoadmportedAssets();
	static std::vector<BinaryExporter::AssetIndex>& GetImportedAssets();

private:
	static std::vector<BinaryExporter::AssetIndex> myLoadedMeshes;
};

