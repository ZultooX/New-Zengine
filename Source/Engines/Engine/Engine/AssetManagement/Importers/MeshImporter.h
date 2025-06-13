#pragma once

#include <Engine/AssetManagement/AssetsCommon.hpp>
#include <vector>

namespace TGA::FBX { struct Mesh; }

class Mesh;
class MeshImporter
{
	friend class MeshExporter;


	// Used by the exporter to load and export objects.
#pragma region [LOAD FROM PATH]

#ifdef _DEBUG
private:
	static void LoadAllMeshes(std::vector<MeshData>& aOutAssetList);

private:
	static void Load_FBX(const char* aPath, std::vector<MeshData>& aOutAssetList);
	static void Load_OBJ(const char* aPath, std::vector<MeshData>& aOutAssetList);

	static void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, std::vector<MeshData>& aOutAssetList);
#endif

#pragma endregion



#pragma region [ASSET EXPORTING]

public:
	static void Load(const size_t& aID, Mesh& aOutAsset);

	static void LoadExportedAssets();
	static std::vector<BinaryExporter::MeshIndex>& GetExportedAssets();

#pragma endregion


	static void Unload(Mesh& aOutAsset);


private:
	static std::vector<BinaryExporter::MeshIndex> myLoadedMeshes;
};

