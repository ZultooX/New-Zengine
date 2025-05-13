#pragma once

#include "AssetImporter.h"
#include "../Assets/Mesh.h"
namespace TGA::FBX
{
	struct Mesh;
}

class MeshImporter : public AssetImporter<Assets::Mesh>
{
public:
	void Load(const char* aPath, void* aOutAsset) override;

private:
	void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, Assets::Mesh* aOutMesh);


	void LoadFBX(const char* aPath, void* aOutAsset);
};