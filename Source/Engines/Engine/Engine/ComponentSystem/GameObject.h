#pragma once

#include <Engine/Utilities/BitMask.hpp>
#include "ComponentManager.h"

namespace Zengine::ComponentSystem
{
	class GameObject final
	{
	public:
		GameObject();
		GameObject(const int& aId);

	public:
		template <typename T>
		T* AddComponent();

		template <typename T>
		T* GetComponent(const int& aIdx = 0);

		template <typename T>
		void RemoveComponent(const int& aIdx = 0);

	private:
		int myID = -1;
		Utilities::BitMask<> myBitmask;
	};



	template<typename T>
	inline T* GameObject::AddComponent()
	{
		return ComponentManager::AddComponent<T>(myID);
	}
	
	template<typename T>
	inline T* GameObject::GetComponent(const int& aIdx)
	{
		return ComponentManager::GetComponent<T>(myID, aIdx);
	}
	
	template<typename T>
	inline void GameObject::RemoveComponent(const int& aIdx)
	{
		ComponentManager::RemoveComponent<T>(myID, aIdx);
	}
}

namespace CS = Zengine::ComponentSystem;