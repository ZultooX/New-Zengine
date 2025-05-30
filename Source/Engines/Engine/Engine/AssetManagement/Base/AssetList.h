#pragma once

#include <unordered_map>
#include <utility>
#include <filesystem>
#include "CommonAssetUtils.h"

class BaseList { public: BaseList() = default; virtual ~BaseList() = default; };

template<typename T, typename ID = size_t>
class AssetList final : public BaseList
{
public:
	AssetList();

public:
	void Add(T* anAsset);

	void Remove(const T& anAsset);
	void Remove(const char* aPath);
	void Remove(const size_t& anAssetID);

	bool Exists(const T& anAsset);
	bool Exists(const char* aPath);
	bool Exists(const size_t& anAssetID);

	T* Get(const char* aPath);
	T* Get(const size_t& anAssetID);

	size_t GetSize() const;

private:
	std::unordered_map<size_t, T*> myLoadedAssets;

	const int listExpansionAmount = 10;
};

template<typename T, typename ID>
inline AssetList<T, ID>::AssetList()
{
	//myLoadedAssets.reserve(listExpansionAmount);
}

template<typename T, typename ID>
inline void AssetList<T, ID>::Add(T* anAsset)
{
	//if (myLoadedAssets.size() > myLoadedAssets.capacity()) 
	//	myLoadedAssets.reserve(myLoadedAssets.capacity() + listExpansionAmount);

	//myIdToIndex[anAsset->GetID()] = myLoadedAssets.size();
	myLoadedAssets[anAsset->GetID()] = anAsset;
}

template<typename T, typename ID>
inline void AssetList<T, ID>::Remove(const T& anAsset)
{
	Remove(anAsset.GetPath());
}

template<typename T, typename ID>
inline void AssetList<T, ID>::Remove(const char* aPath)
{
	size_t id = GetIdFromPath(aPath);

	Remove(id);
}

template<typename T, typename ID>
inline void AssetList<T, ID>::Remove(const size_t& anAssetID)
{
	auto it = myLoadedAssets.find(anAssetID);
	if (it == myLoadedAssets.end()) return;

	delete myLoadedAssets[anAssetID];
	myLoadedAssets[anAssetID] = nullptr;

	myLoadedAssets.erase(anAssetID);
}

template<typename T, typename ID>
inline bool AssetList<T, ID>::Exists(const T& anAsset)
{
	return Exists(anAsset.GetPath());
}

template<typename T, typename ID>
inline bool AssetList<T, ID>::Exists(const char* aPath)
{
	size_t id = GetIdFromPath(aPath);

	return Exists(id);
}

template<typename T, typename ID>
inline bool AssetList<T, ID>::Exists(const size_t& anAssetID)
{
	auto it = myLoadedAssets.find(anAssetID);
	if (it == myLoadedAssets.end()) return false;

	return it->second != nullptr;
}

template<typename T, typename ID>
inline T* AssetList<T, ID>::Get(const char* aPath)
{
	size_t id = GetIdFromPath(aPath);

	return Get(id);
}

template<typename T, typename ID>
inline T* AssetList<T, ID>::Get(const size_t& anAssetID)
{
	auto idToIndex = myLoadedAssets.find(anAssetID);
	if (idToIndex == myLoadedAssets.end()) return nullptr;

	return idToIndex->second;
}

template<typename T, typename ID>
inline size_t AssetList<T, ID>::GetSize() const
{
	return myLoadedAssets.size();
}
