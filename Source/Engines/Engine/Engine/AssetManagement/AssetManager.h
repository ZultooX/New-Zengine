#pragma once
#include <string>
#include <string_view>
#include <functional>

#include <Engine/AssetManagement/Base/AssetList.h>
#include <Engine/AssetManagement/Base/AssetPointer.h>
#include <Engine/AssetManagement/Base/AssetImporter.h>

#include <unordered_map>
#include <typeindex>

class AssetManager
{
public:
	template<typename T>
	static AssetPointer<T> GetFromPath(const char* aPath);

	template<typename T>
	static AssetPointer<T> GetFromID(const size_t& anID);

	template <typename T>
	static AssetPointer<T> LoadAsset(const size_t& anID);

	template<typename T>
	static void RemoveAsset(T& anAsset);

private:
	static std::unordered_map<std::type_index, BaseList*> AssetLists;
};

template<typename T>
AssetPointer<T> AssetManager::GetFromPath(const char* aPath)
{
	const size_t id = std::hash<std::string>{}(std::string(aPath));
	AssetPointer<T> ptr = AssetManager::LoadAsset<T>(id);
	return ptr;
}


template<typename T>
inline AssetPointer<T> AssetManager::GetFromID(const size_t& anID)
{
	AssetPointer<T> ptr = AssetManager::LoadAsset<T>(anID);
	return ptr;
}



template<typename T>
inline AssetPointer<T> AssetManager::LoadAsset(const size_t& anID)
{
	std::type_index type = typeid(T);

	AssetList<T>* assetList = static_cast<AssetList<T>*>(AssetLists[type]);
	if (!assetList->Exists(anID))
	{
		T* asset = new T(anID);
		assetList->Add(asset);
	}

	T* addedAsset = assetList->Get(anID);
	return AssetPointer<T>(addedAsset, assetList);
}

template<typename T>
inline void AssetManager::RemoveAsset(T& anAsset)
{
	std::type_index type = typeid(T);

	AssetList<T>* assetList = static_cast<AssetList<T>*>(AssetLists[type]);
	if (assetList->Exists(anAsset)) assetList->Remove(anAsset);
}

















//template<typename T>
//inline AssetPointer<T> AssetManager::Get(const char* anAssetPath)
//{

//}
//
//template<typename T>
//inline AssetPointer<T> AssetManager::Get(const size_t& anID)
//{
//	return AssetPointer<T>();
//}
//
//template<typename T>
//inline T* AssetManager::GetRawAsset(const size_t& anID)
//{

//