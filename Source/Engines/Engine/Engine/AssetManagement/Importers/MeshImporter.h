#pragma once

#include <Engine/AssetManagement/AssetsCommon.hpp>
#include <vector>

namespace TGA::FBX { struct Mesh; }

class Mesh;
class MeshImporter
{
public:
	static void Load(const char* aPath, std::vector<MeshData>& aOutAssetList);

private:
	static void Load_FBX(const char* aPath, std::vector<MeshData>& aOutAssetList);
	static void Load_OBJ(const char* aPath, std::vector<MeshData>& aOutAssetList);

	static void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, std::vector<MeshData>& aOutAssetList);







public:
	static void Load(const size_t& aID, Mesh& aOutAsset);
	static void Load(const char* aPath, Mesh& aOutAsset);
	static void Unload(Mesh& aOutAsset);

	static void LoadmportedAssets();
	static std::vector<BinaryExporter::MeshIndex>& GetImportedAssets();

private:
	static void Load_FBX(const char* aPath, Mesh& aOutAsset);
	static void Load_OBJ(const char* aPath, Mesh& aOutAsset);

private:
	static void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, Mesh& aOutMesh);

	static std::vector<BinaryExporter::MeshIndex> myLoadedMeshes;
};

