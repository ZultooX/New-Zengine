#include "MeshManager.h"

#include <Engine/Editor/DebugLogger.h>

#include <Engine/Importers/MeshImporter.h>


void MeshManager::Init()
{
	MeshImporter::Init();
}

Mesh* MeshManager::Load(const std::string& aMeshPath)
{
	Mesh* mesh = MeshImporter::Load(aMeshPath);

	myAssets.emplace_back();
	unsigned idx = (unsigned)myAssets.size();

	myPathToIdx[aMeshPath] = idx;

	return mesh;
}