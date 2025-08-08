#include "MeshLoader.h"

#include <TgaFbx/TgaFbxStructs.h>
#include <TgaFbx/Importer.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

namespace Zengine
{
	enum class Importers
	{
		FBX, OBJ
	};

	void MeshLoader::Load(const char* path, Zengine::Mesh& mesh, const unsigned& idx)
	{
		static std::unordered_map<const char*, Importers> supportedFiles = {
			{ ".fbx" , Importers::FBX },
			{ ".obj" , Importers::OBJ },
		};

		std::vector<MeshData> meshList;

		Importers importer = supportedFiles[path];

		switch (importer)
		{
		case Importers::FBX: Load_FBX(path, meshList); break;
		case Importers::OBJ: Load_OBJ(path, meshList); break;
		}

		mesh.SetIndicies(meshList[idx].indicies);
		mesh.SetVerticies(meshList[idx].verticies);
		mesh.SetName(meshList[idx].meshName);
		mesh.SetPath(path);
	}

	void MeshLoader::Load_FBX(const char* aPath, std::vector<MeshData>& aOutAssetList)
	{
		static bool importerInitialized = false;
		if (!importerInitialized)
		{
			TGA::FBX::Importer::InitImporter();
			importerInitialized = true;
		}

		TGA::FBX::Mesh tgaMesh;
		TGA::FBX::FbxImportStatus status = TGA::FBX::Importer::LoadMesh(aPath, tgaMesh);

		ConvertFromTGAMesh(tgaMesh, aOutAssetList);
	}

	void MeshLoader::Load_OBJ(const char* aPath, std::vector<MeshData>& aOutAssetList)
	{
	}

	void MeshLoader::ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, std::vector<MeshData>& aOutAssetList)
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		for (const TGA::FBX::Mesh::Element& element : aMesh.Elements)
		{
			aOutAssetList.push_back({});
			MeshData& mesh = aOutAssetList.back();

			mesh.meshName = element.MeshName;

			mesh.indicies.resize(element.Indices.size());
			memcpy(mesh.indicies.data(), element.Indices.data(), sizeof(unsigned) * element.Indices.size());

			mesh.verticies.reserve(element.Vertices.size());

			for (const TGA::FBX::Vertex& vert : element.Vertices)
			{
				Vertex vertex;
				vertex.position = Vector4f(vert.Position[0], vert.Position[1], vert.Position[2], vert.Position[3]);

				vertex.normal = Vector3f(vert.Normal[0], vert.Normal[1], vert.Normal[2]);
				vertex.binormal = Vector3f(vert.BiNormal[0], vert.BiNormal[1], vert.BiNormal[2]);
				vertex.tangent = Vector3f(vert.Tangent[0], vert.Tangent[1], vert.Tangent[2]);

				vertex.boneIDs = Vector4Int(vert.BoneIDs[0], vert.BoneIDs[1], vert.BoneIDs[2], vert.BoneIDs[3]);
				vertex.boneWeights = Vector4f(vert.BoneWeights[0], vert.BoneWeights[1], vert.BoneWeights[2], vert.BoneWeights[3]);

				vertex.color0 = Vector4f(vert.VertexColors[0][0], vert.VertexColors[0][1], vert.VertexColors[0][2], vert.VertexColors[0][3]);
				vertex.color1 = Vector4f(vert.VertexColors[1][0], vert.VertexColors[1][1], vert.VertexColors[1][2], vert.VertexColors[1][3]);
				vertex.color2 = Vector4f(vert.VertexColors[2][0], vert.VertexColors[2][1], vert.VertexColors[2][2], vert.VertexColors[2][3]);
				vertex.color3 = Vector4f(vert.VertexColors[3][0], vert.VertexColors[3][1], vert.VertexColors[3][2], vert.VertexColors[3][3]);

				vertex.uv0 = Vector2f(vert.UVs[0][0], vert.UVs[0][1]);
				vertex.uv1 = Vector2f(vert.UVs[1][0], vert.UVs[1][1]);
				vertex.uv2 = Vector2f(vert.UVs[2][0], vert.UVs[2][1]);
				vertex.uv3 = Vector2f(vert.UVs[3][0], vert.UVs[3][1]);

				mesh.verticies.push_back(vertex);
			}
		}
	}
}