#pragma once

#include <Engine/AssetManagement/Base/Asset.h>		
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Importers/MeshImporter.h>
#include <Engine/AssetManagement/Exporters/MeshExporter.h>

#include <GraphicsEngine/GraphicsStructs.h>
#include <vector>

struct ID3D11Buffer;
class Mesh : public Asset
{
	BASE_ASSET(Mesh, MeshImporter, MeshExporter)

public:
	const std::string& GetName() const;
	void SetName(const std::string& aName);

	const std::vector<Vertex>& GetVerticies() const;
	const std::vector<unsigned>& GetIndicies() const;

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* const* GetVertexBufferAddr();

	ID3D11Buffer* GetIndexBuffer();
	ID3D11Buffer* const* GetIndexBufferAddr();

private:
	void Release();

private:
	std::string meshName = "";

	std::vector<Vertex> verticies;
	std::vector<unsigned> indicies;

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
};