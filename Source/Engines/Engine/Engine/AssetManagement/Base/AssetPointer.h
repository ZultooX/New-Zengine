#pragma once

#include <Engine/AssetManagement/Base/AssetList.h>

template <typename T>
class AssetPointer
{
	friend class AssetManager;


public:
	inline AssetPointer(T* aAsset, AssetList<T>* aAssetList) : myAssetID(aAsset->GetID()), pAssetList(aAssetList)
    { 
        pAssetList->Get(myAssetID)->IncrementRefs();
    }

	AssetPointer() = default;
	inline ~AssetPointer() { if(pAssetList) if(pAssetList->Get(myAssetID)) pAssetList->Get(myAssetID)->DecrementRefs(); }
    
    AssetPointer(const AssetPointer& other)
        : myAssetID(other.myAssetID), pAssetList(other.pAssetList)
    {
        if (pAssetList && pAssetList->Get(myAssetID))
            pAssetList->Get(myAssetID)->IncrementRefs();
    }

    // MOVE CONSTRUCTOR
    AssetPointer(AssetPointer&& other) noexcept
        : myAssetID(other.myAssetID), pAssetList(other.pAssetList)
    {
        other.myAssetID = 0;
        other.pAssetList = nullptr;
    }

    T* Get();
    const T* Get() const;

	T* operator ->() { return pAssetList->Get(myAssetID); }
	const T* operator ->() const { return pAssetList->Get(myAssetID); }
	AssetPointer<T>& operator=(const AssetPointer<T>& aOther);

    explicit operator bool() const noexcept {
        return pAssetList != nullptr;
    }
private:
	size_t myAssetID = 0;
    AssetList<T>* pAssetList = nullptr;
};

template<typename T>
inline T* AssetPointer<T>::Get()
{
    return pAssetList->Get(myAssetID);
}

template<typename T>
inline const T* AssetPointer<T>::Get() const
{
    return pAssetList->Get(myAssetID);
}

template<typename T>
AssetPointer<T>& AssetPointer<T>::operator=(const AssetPointer<T>& aOther)
{
    if (this != &aOther) 
    {
        if(myAssetID != 0) pAssetList->Get(myAssetID)->DecrementRefs();

        myAssetID = aOther.myAssetID;
        pAssetList = aOther.pAssetList;

        if(myAssetID != 0) pAssetList->Get(myAssetID)->IncrementRefs();
    }

    return *this;
}
