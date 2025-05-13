#include "Mesh.h"


void Assets::Mesh::SetMeshData(const MeshData& someMeshData)
{
	myMesh = someMeshData;
}

void Assets::Mesh::AddSubMesh() { myMesh.meshes.push_back(SubMesh{}); }

SubMesh& Assets::Mesh::GetLastSubmesh() { return myMesh.meshes.back(); }
const SubMesh& Assets::Mesh::GetSubmesh(const unsigned& aIdx) { return myMesh.meshes[aIdx]; }
const std::vector<SubMesh>& Assets::Mesh::GetSubmeshes() { return myMesh.meshes; }
bool Assets::Mesh::HasSkeleton() const { return myMesh.skeleton != nullptr; }
const Skeleton* Assets::Mesh::GetSkeleton() const { return myMesh.skeleton; }
