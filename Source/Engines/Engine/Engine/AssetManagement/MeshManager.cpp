#include "MeshManager.h"

#include <Engine/Editor/DebugLogger.h>

#include <Engine/Importers/MeshImporter.h>
#include <TgaFbx/Importer.h>
#include <TgaFbx/TGAFbx.h>
#include <TgaFbx/TgaFbxStructs.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#include <GraphicsEngine/DX11/Buffers/BufferManager.h>

void MeshManager::Init()
{
	//MeshImporter::Init();
	TGA::FBX::Importer::InitImporter();
}

Mesh* MeshManager::Load(const std::string& aMeshPath)
{
	TGA::FBX::Mesh tgaMesh;
	TGA::FBX::FbxImportStatus status = TGA::FBX::Importer::LoadMesh(aMeshPath, tgaMesh);

	if (status.Result == TGA::FBX::FbxImportResult::FileNotFound)
	{
		DebugLogger::LogError("MeshFile not found at path not found: " + aMeshPath);
		return nullptr;
	}
	else if (status.Result == TGA::FBX::FbxImportResult::NoMeshData)
	{
		DebugLogger::LogError("File has no mesh data: " + aMeshPath);
		return nullptr;
	}

	Mesh* mesh = new Mesh;
	ConvertFromTGAMesh(tgaMesh, mesh);

	myAssets.emplace_back();
	unsigned idx = (unsigned)myAssets.size();

	myPathToIdx[aMeshPath] = idx;

	return mesh;
}

void MeshManager::ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, Mesh* aOutMesh)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	aOutMesh->path = aMesh.Name;

	for (const TGA::FBX::Mesh::Element& element : aMesh.Elements)
	{
		aOutMesh->meshes.push_back(SubMesh());

		aOutMesh->meshes.back().materialIndex = element.MaterialIndex;

		aOutMesh->meshes.back().meshName = element.MeshName;

		aOutMesh->meshes.back().indicies.resize(element.Indices.size());
		memcpy(aOutMesh->meshes.back().indicies.data(), element.Indices.data(), sizeof(unsigned) * element.Indices.size());

		aOutMesh->meshes.back().verticies.reserve(element.Vertices.size());

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

			vertex.uv0= Vector2f(vert.UVs[0][0], vert.UVs[0][1]);
			vertex.uv1= Vector2f(vert.UVs[1][0], vert.UVs[1][1]);
			vertex.uv2= Vector2f(vert.UVs[2][0], vert.UVs[2][1]);
			vertex.uv3= Vector2f(vert.UVs[3][0], vert.UVs[3][1]);

			aOutMesh->meshes.back().verticies.push_back(vertex);
		}

		unsigned size = 0;
		
		{ // Indicies
			size = (sizeof(unsigned) * aOutMesh->meshes.back().indicies.size());

			D3D11_BUFFER_DESC indexBufferDesc = {};
			indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			indexBufferDesc.ByteWidth = size;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = aOutMesh->meshes.back().indicies.data();

			ge->GetDevice()->CreateBuffer(&indexBufferDesc, &data, &aOutMesh->meshes.back().indexBuffer);
		}


		{ // Vertex Buffer
			size = sizeof(Vertex) * aOutMesh->meshes.back().verticies.size();

			D3D11_BUFFER_DESC vertexBufferDesc = {};
			vertexBufferDesc.ByteWidth = size;
			vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = aOutMesh->meshes.back().verticies.data();


			ge->GetDevice()->CreateBuffer(&vertexBufferDesc, &data, &aOutMesh->meshes.back().vertexBuffer);
		}
	}
}
