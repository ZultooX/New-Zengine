#include "MeshImporter.h"

#include <filesystem>

#include <TgaFbx/TGAFbx.h>
#include <TgaFbx/Importer.h>
#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

void MeshImporter::Load(const char* aPath, void* aOutAsset)
{
	const std::string extension = std::filesystem::path(aPath).extension().string();

	if (extension == ".fbx") LoadFBX(aPath, aOutAsset);
}

void MeshImporter::LoadFBX(const char* aPath, void* aOutAsset)
{
	TGA::FBX::Mesh mesh;
	TGA::FBX::Importer::LoadMesh(aPath, mesh);

	ConvertFromTGAMesh(mesh, (Assets::Mesh*)aOutAsset);
}






void MeshImporter::ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, Assets::Mesh* aOutMesh)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	aOutMesh->SetName(aMesh.Name);

	for (const TGA::FBX::Mesh::Element& element : aMesh.Elements)
	{
		aOutMesh->AddSubMesh();
		SubMesh& sub = aOutMesh->GetLastSubmesh();

		sub.materialIndex = element.MaterialIndex;


		sub.meshName = element.MeshName;

		sub.indicies.resize(element.Indices.size());
		memcpy(sub.indicies.data(), element.Indices.data(), sizeof(unsigned) * element.Indices.size());

		sub.verticies.reserve(element.Vertices.size());

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

			sub.verticies.push_back(vertex);
		}

		unsigned size = 0;

		{ // Indicies
			size = (sizeof(unsigned) * sub.indicies.size());

			D3D11_BUFFER_DESC indexBufferDesc = {};
			indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			indexBufferDesc.ByteWidth = size;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = sub.indicies.data();

			ge->GetDevice()->CreateBuffer(&indexBufferDesc, &data,  &sub.indexBuffer);
		}


		{ // Vertex Buffer
			size = sizeof(Vertex) * sub.verticies.size();

			D3D11_BUFFER_DESC vertexBufferDesc = {};
			vertexBufferDesc.ByteWidth = size;
			vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = sub.verticies.data();


			ge->GetDevice()->CreateBuffer(&vertexBufferDesc, &data, &sub.vertexBuffer);
		}
	}
}