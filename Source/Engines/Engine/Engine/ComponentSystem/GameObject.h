#pragma once

#include <Engine/Utilities/BitMask.hpp>
#include "ComponentManager.h"
 
namespace Zengine::ComponentSystem
{
	class Transform;
	class GameObject final
	{
	public:
		static GameObject* Create();
		static GameObject* Create(const int& aId);

		~GameObject();

	public:
		template <typename T>
		T* AddComponent();

		template <typename T>
		T* GetComponent(const int& aIdx = 0);

		template <typename T>
		void RemoveComponent(const int& aIdx = 0);

	public:
		void SetID(const int aId);
		const int& GetID() { return myID; }
		inline void SetName(const std::string& aName) { myName = aName; }
		inline const std::string& GetName() { return myName; }
		inline const std::string& GetName() const { return myName; }


		Transform* transform;

	private:
		std::string myName = "New Gameobject";

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