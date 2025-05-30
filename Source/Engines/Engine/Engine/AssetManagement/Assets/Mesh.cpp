#include "Mesh.h"

const SubMesh& Mesh::GetLastSubmesh() const { return myMeshes.back(); }
SubMesh& Mesh::GetLastSubmesh() { return myMeshes.back(); }

const std::vector<SubMesh>& Mesh::GetSubmeshes() const { return myMeshes; }
std::vector<SubMesh>& Mesh::GetSubmeshes() { return myMeshes; }

void Mesh::AddSubmesh() { myMeshes.push_back({}); }


void Mesh::Release()
{
	for (SubMesh& mesh : myMeshes)
	{
		mesh.indexBuffer->Release();
		mesh.vertexBuffer->Release();
	}
}
