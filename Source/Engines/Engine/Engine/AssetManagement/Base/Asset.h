#pragma once

#include <string>
#include <string_view>
#include <functional>
#include <filesystem>

#include <Engine/AssetManagement/Base/AssetPointer.h>
#include <Engine/AssetManagement/Base/CommonAssetUtils.h>
#include <Engine/AssetManagement/Base/AssetMacros.h>

#include <Engine/Utilities/BitMask.hpp>

class Asset
{
	friend class AssetPointer<Asset>;

protected:
	Asset(const char* aPath) :
		myPath(std::string(aPath)),
		myID(GetIdFromPath(aPath)),
		myName(std::filesystem::path(aPath).filename().stem().string())
	{};

	Asset(const size_t& aID) :
		myID(aID)
	{};
	Asset() = default;
	virtual ~Asset() = default;

	Asset& operator = (Asset&& other) noexcept
	{
		std::swap(myPath, other.myPath);
		std::swap(myName, other.myName);
		std::swap(myID, other.myID);
	}

protected:
	inline void IncrementRefs() { myReferencesCount++; }
	virtual void DecrementRefs() = 0;

	void SetDirty();
	void ClearDirty();
	bool IsDirty();

	Zengine::Utilities::BitMask<> myFlags;

	enum class Flags
	{
		Dirty
	};

public:
	inline const size_t& GetID() const { return myID; }
	inline const char* GetPath() const { return myPath.c_str(); }
	inline const char* GetName() const { return myName.c_str(); }

private:
	std::string myPath = "";
	std::string myName = "";
	size_t myID = 0;

protected:
	unsigned myReferencesCount = 0;  // This is used to calculate how many items use this specific asset.
};