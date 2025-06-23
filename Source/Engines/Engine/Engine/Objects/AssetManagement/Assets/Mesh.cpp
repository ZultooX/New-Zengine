#include "Mesh.h"

#include <d3d11.h>
#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

namespace Zengine
{
	Mesh::Mesh(const std::vector<Vertex>& _verticies, const std::vector<unsigned>& _indicies) : Asset()
	{
		indicies.insert(indicies.begin(), _indicies.begin(), _indicies.end());
		verticies.insert(verticies.begin(), _verticies.begin(), _verticies.end());

		UpdateMesh();
	}

	Mesh::Mesh() : Asset() {}
	Mesh::Mesh(const size_t& _id) : Asset(_id) {}

	const std::vector<unsigned>& Mesh::GetIndicies() const { return indicies; }
	std::vector<unsigned>& Mesh::GetIndicies() { return indicies; }
	void Mesh::SetIndicies(const std::vector<unsigned>& indList) { indicies.insert(indicies.begin(), indList.begin(), indList.end()); }

	const std::vector<Vertex>& Mesh::GetVerticies() const { return verticies; }
	std::vector<Vertex>& Mesh::GetVerticies() { return verticies; }
	void Mesh::SetVerticies(const std::vector<Vertex>& vertList) { verticies.insert(verticies.begin(), vertList.begin(), vertList.end()); }

	void Mesh::UpdateMesh()
	{
		if (indexBuffer)
		{
			indexBuffer->Release();
			indexBuffer = nullptr;
		}

		if (vertexBuffer)
		{
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}

		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		// Create index buffer
		{
			D3D11_BUFFER_DESC indexBufferDesc = {};
			indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(unsigned) * indicies.size());
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA indexSubData = {};
			indexSubData.pSysMem = indicies.data();

			ge->GetDevice()->CreateBuffer(&indexBufferDesc, &indexSubData, &indexBuffer);
		}

		// Create vertex buffer
		{
			D3D11_BUFFER_DESC vertexBufferDesc = {};
			vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * verticies.size());
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA vertexSubData = {};
			vertexSubData.pSysMem = verticies.data();

			ge->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubData, &vertexBuffer);
		}
	}
}