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
		AssetPointer(const size_t& assetId, List<T>* _list);

		T& operator->();

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
}