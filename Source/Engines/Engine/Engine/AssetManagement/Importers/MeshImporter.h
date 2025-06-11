#pragma once
#include <Engine/AssetManagement/AssetsCommon.hpp>

namespace TGA::FBX { struct Mesh; }

class Mesh;
class MeshImporter
{
public:
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

