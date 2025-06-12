#pragma once

#include <Engine/AssetManagement/AssetsCommon.hpp>
#include <vector>

namespace TGA::FBX { struct Mesh; }

class Mesh;
class MeshImporter
{
#pragma region [LOAD FROM PATH]

public:
	static void LoadAllMeshes(const char* aPath, std::vector<MeshData>& aOutAssetList);

private:
	static void Load_FBX(const char* aPath, std::vector<MeshData>& aOutAssetList);
	static void Load_OBJ(const char* aPath, std::vector<MeshData>& aOutAssetList);

	static void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, std::vector<MeshData>& aOutAssetList);

#pragma endregion

#pragma region [LOAD FROM ID]

public:
	static void Load(const size_t& aID, Mesh& aOutAsset);


#pragma endregion

	static void LoadExportedAssets();
	static std::vector<BinaryExporter::MeshIndex>& GetImportedAssets();

	static void Unload(Mesh& aOutAsset);


private:
	static void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, Mesh& aOutMesh);

	static std::vector<BinaryExporter::MeshIndex> myLoadedMeshes;
};

