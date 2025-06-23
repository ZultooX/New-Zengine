#pragma once

#include <Engine/Objects/AssetManagement/Base/Asset.h>
#include <Engine/Objects/AssetManagement/Assets/Mesh.h>
#include <Engine/Objects/AssetManagement/AssetLoaders/MeshLoader.h>

#include <GraphicsEngine/GraphicsStructs.h>

#include <vector>

struct ID3D11Buffer;
namespace Zengine
{
	class Mesh final : public Asset
	{
	public:
		Mesh(const std::vector<Vertex>& _verticies, const std::vector<unsigned>& _indicies);

		Mesh();
		Mesh(const size_t& _id);
		virtual ~Mesh() = default;

	public:
		const std::vector<unsigned>& GetIndicies() const;
		std::vector<unsigned>& GetIndicies();
		void SetIndicies(const std::vector<unsigned>& indList);

		const std::vector<Vertex>& GetVerticies() const;
		std::vector<Vertex>& GetVerticies();
		void SetVerticies(const std::vector<Vertex>& vertList);

	private:
		void UpdateMesh();

	private:
		std::vector<unsigned> indicies;
		std::vector<Vertex> verticies;

		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;
	};
}