#pragma once

#include <Engine/New AssetManagement/Importers/MeshImporter.h>
#include <Engine/New AssetManagement/Assets/Mesh.h>


#include <unordered_map>
#include <typeindex>
#include <vector>

enum AssetType : int
{
	MESH, TEXTURE
};

#include <Engine/Editor/DebugLogger.h>


class MeshImporter;
class AssetManager
{
public:
	static void Init();

	template<typename T>
	static T* GetFromPath(const char* aPath);

	template<typename T>
	static T* GetFromID(const size_t& aID);
	
	template<typename T>
	static std::vector<T*> GetAssetsOfType();

	// ptrs to all importers

private:
	static MeshImporter* _MeshImporter;

	static const std::unordered_map<std::type_index, AssetType> TypeToEnumType;
	static std::unordered_map<size_t, Asset*> IdToAsset;
};

template<typename T>
inline T* AssetManager::GetFromPath(const char* aPath)
{
	const std::type_index type = typeid(T);
	
	if (TypeToEnumType.find(type) == TypeToEnumType.end())
		DebugLogger::LogWarning("Asset Importer not implemented.");

	static std::hash<const char*> hasher = std::hash<const char*>();
	size_t id = hasher(aPath); 

	if (IdToAsset.find(id) == IdToAsset.end())
	{
		IdToAsset[id] = new T;
		IdToAsset[id]->SetID(id);

		const AssetType eType = TypeToEnumType.at(type);
		switch (eType)
		{
		case AssetType::MESH:
			_MeshImporter->Load(aPath, IdToAsset[id]);
			break;
		}

		return static_cast<T*>(IdToAsset[id]);
	}

	return GetFromID<T>(id);
}

template<typename T>
inline T* AssetManager::GetFromID(const size_t& aID)
{
	if (IdToAsset.find(aID) == IdToAsset.end())
		DebugLogger::LogWarning("No exist.");

	return static_cast<T*>(IdToAsset[aID]);
}

template<typename T>
inline std::vector<T*> AssetManager::GetAssetsOfType()
{
	std::vector<T*> assets;
	for (auto& [id, asset] : IdToAsset) {
		if (T* ass = dynamic_cast<T*>(asset))
			assets.push_back(ass);
	}

	return assets;
}
