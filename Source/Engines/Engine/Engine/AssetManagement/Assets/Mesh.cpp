#include "Mesh.h"

const std::string& Mesh::GetName() const { return meshName; }
void Mesh::SetName(const std::string& aName) { meshName = aName; }

const std::vector<Vertex>& Mesh::GetVerticies() const { return verticies; }
const std::vector<unsigned>& Mesh::GetIndicies() const { return indicies; }

ID3D11Buffer* Mesh::GetVertexBuffer() { return vertexBuffer; }
ID3D11Buffer* const* Mesh::GetVertexBufferAddr() { return &vertexBuffer; }

ID3D11Buffer* Mesh::GetIndexBuffer() { return indexBuffer; }
ID3D11Buffer* const* Mesh::GetIndexBufferAddr() { return &indexBuffer; }


void Mesh::Release()
{
	indexBuffer->Release();
	vertexBuffer->Release();
}
