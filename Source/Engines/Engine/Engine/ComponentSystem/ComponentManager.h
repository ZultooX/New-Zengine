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
	private:
		static void Awake();
		static void Start();
		static void Update();
		static void LateUpdate();

	public:
		static void UpdateManager();

	public:
		template<typename T>
		static T* AddComponent(const int& aGameObjID);

		template<typename T>
		static T* GetComponent(const int& aGameObjID, const int& aIdx = 0);

		template <typename T>
		static void RemoveComponent(const int& aGameObjID, const int& aIdx = 0);

		template <typename T>
		static std::vector<T*>& GetComponents();

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

	template<typename T>
	inline std::vector<T*>& ComponentManager::GetComponents()
	{
		std::type_index type = typeid(T);
		if (myGameObjectIdToIdx.find(type) == myGameObjectIdToIdx.end())
		{
			static std::vector<T*> vec;
			return vec;
		}

		return ((ComponentPool<T>*)myComponentPools[myGameObjectIdToIdx[type]])->GetComponents();
	}
}

namespace CS = Zengine::ComponentSystem;