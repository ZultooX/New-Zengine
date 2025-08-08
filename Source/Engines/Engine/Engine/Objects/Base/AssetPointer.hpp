#pragma once

#include <Engine/Objects/Base/List.hpp>

#include <string>
#include <Zultools/BitMask.hpp>

namespace Zengine
{
	template<typename T>
	class AssetPointer 
	{
	public:
		AssetPointer() = default;
		AssetPointer(const AssetPointer& other)
			: id(other.id), list(other.list)
		{

		}

		// MOVE CONSTRUCTOR
		AssetPointer(AssetPointer&& other) noexcept
			: id(other.id), list(other.list)
		{
			other.id = 0;
			other.list = nullptr;
		}

	public:
		AssetPointer(const size_t& assetId, List<T>* _list);

		T& operator->();
		AssetPointer<T>& operator=(const AssetPointer<T>& aOther);

	private:
		const size_t id;
		List<T>* list;
	};

	template<typename T>
	inline T& AssetPointer<T>::operator->()
	{
		return list->GetOrAdd(id);
	}
	

	template<typename T>
	inline AssetPointer<T>::AssetPointer(const size_t& assetId, List<T>* _list) 
		: id(assetId), list(_list) { }

	template<typename T>
	AssetPointer<T>& AssetPointer<T>::operator=(const AssetPointer<T>& aOther)
	{
		return *this;
	}
}