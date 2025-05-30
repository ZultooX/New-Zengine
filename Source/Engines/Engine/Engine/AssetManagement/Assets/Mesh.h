#pragma once

#include <Engine/AssetManagement/Base/Asset.h>		
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Importers/MeshImporter.h>
#include <Engine/AssetManagement/Exporters/MeshExporter.h>

#include <GraphicsEngine/GraphicsStructs.h>
#include <vector>

class Mesh : public Asset
{
	BASE_ASSET(Mesh, MeshImporter, MeshExporter)

public:
	const SubMesh& GetLastSubmesh() const;
	SubMesh& GetLastSubmesh();

	const std::vector<SubMesh>& GetSubmeshes() const;
	std::vector<SubMesh>& GetSubmeshes();

	void AddSubmesh();

private:
	void Release();

private:
	std::vector<SubMesh> myMeshes;
};