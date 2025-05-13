#include "AssetManager.hpp"
#include <TgaFbx/Importer.h>

const std::unordered_map<std::type_index, AssetType> AssetManager::TypeToEnumType = 
{
	{typeid(Assets::Mesh), AssetType::MESH}
};
MeshImporter* AssetManager::_MeshImporter;
std::unordered_map<size_t, Asset*> AssetManager::IdToAsset;


void AssetManager::Init()
{
	_MeshImporter = new MeshImporter;
	_MeshImporter->Init();

	TGA::FBX::Importer::InitImporter();
}
