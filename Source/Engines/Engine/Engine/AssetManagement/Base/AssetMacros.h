#pragma once

#define BASE_ASSET(assetType, assetImporterClass, assetExporterClass)									\
public:																									\
assetType() = default;																					\
assetType(const char* aPath) : Asset(aPath) { assetImporterClass::Load(aPath, *this); }					\
assetType(const size_t& aID) : Asset(aID)   { assetImporterClass::Load(aID, *this); }					\
assetType(const assetType&) = default;																	\
assetType& operator=(const assetType&) = default;														\
public:																									\
static const char* GetTypeName() {static const char* name = #assetType; return name;}					\
static size_t GetTypeID() { static size_t id = std::hash<std::string_view>{}(#assetType); return id; }	\
friend class AssetPointer<assetType>;																	\
friend class AssetFactory;																				\
friend class AssetManager;																				\
friend class AssetList<assetType>;																				\
friend class assetImporterClass;																		\
protected:																								\
inline void DecrementRefs() override																	\
{																										\
	--myReferencesCount;																				\
	if (myReferencesCount == 0)																			\
	{																									\
		assetImporterClass::Unload(*this);																\
		AssetManager::RemoveAsset<assetType>(*this);													\
	}																									\
}																										\
private: