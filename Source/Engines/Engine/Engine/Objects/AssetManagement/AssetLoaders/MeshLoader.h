#pragma once

#include <vector>
#include <Engine/Objects/AssetManagement/Assets/Mesh.h>
#include <GraphicsEngine/GraphicsStructs.h>

namespace TGA::FBX
{
	struct Mesh;
}

namespace Zengine
{
	class MeshLoader
	{
	public:
		static void Load(const char* path, Mesh& mesh, const unsigned& idx = 0);

	private:
		static void Load_FBX(const char* aPath, std::vector<MeshData>& aOutAssetList);
		static void Load_OBJ(const char* aPath, std::vector<MeshData>& aOutAssetList);

		static void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, std::vector<MeshData>& aOutAssetList);
	};
}