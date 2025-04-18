#pragma once

#include "ComponentPool.h"

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>

namespace Zengine::ComponentSystem
{
	class ComponentManager final
	{
	public:
		template<typename T>
		static T* AddComponent(const int& aGameObjID);

		template<typename T>
		static T* GetComponent(const int& aGameObjID, const int& aIdx = 0);

		template <typename T>
		static void RemoveComponent(const int& aGameObjID, const int& aIdx = 0);

	private:
		static std::unordered_map<std::type_index, int> myGameObjectIdToIdx;
		static std::vector<IComponentPool*> myComponentPools;
	};


	template<typename T>
	inline T* ComponentManager::AddComponent(const int& aGameObjID)
	{
		std::type_index type = typeid(T);
		if (myGameObjectIdToIdx.find(type) == myGameObjectIdToIdx.end())
		{
			myGameObjectIdToIdx[type] = (int)myComponentPools.size();
			myComponentPools.emplace_back(new ComponentPool<T>);
		}

		return ((ComponentPool<T>*)myComponentPools[myGameObjectIdToIdx[type]])->AddComponent(aGameObjID);
	}

	template<typename T>
	inline T* ComponentManager::GetComponent(const int& aGameObjID, const int& aIdx)
	{
		std::type_index type = typeid(T);
		if (myGameObjectIdToIdx.find(type) == myGameObjectIdToIdx.end())
		{
			return nullptr;
		}

		return ((ComponentPool<T>*)myComponentPools[myGameObjectIdToIdx[type]])->GetComponent(aGameObjID, aIdx);
	}

	template<typename T>
	inline void ComponentManager::RemoveComponent(const int& aGameObjID, const int& aIdx)
	{
		std::type_index type = typeid(T);
		if (myGameObjectIdToIdx.find(type) == myGameObjectIdToIdx.end())
		{
			return;
		}

		((ComponentPool<T>*)myComponentPools[myGameObjectIdToIdx[type]])->RemoveComponent(aGameObjID, aIdx);
	}
}