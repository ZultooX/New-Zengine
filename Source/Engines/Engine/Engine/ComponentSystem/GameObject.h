#pragma once

#include <Engine/Utilities/BitMask.hpp>
#include "ComponentManager.h"
#include <vector>

#include <typeindex>
#include <string  >

namespace Zengine::ComponentSystem
{
	class Transform;
	class GameObject final
	{
		friend class GameObjectManager;
		friend class SceneExporter;
		friend class SceneImporter;

	private:
		void NewFrame();

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
		void SetName(std::string aName);
		inline const std::string& GetName() { return myName; }
		inline const std::string& GetName() const { return myName; }

		void AddDirtyComponent(const std::type_index& aType);
		const std::vector<std::type_index>& GetDirtyComponents() const;

		const Utilities::BitMask<>& GetBitmask() const;
		Utilities::BitMask<>& GetBitmask();
		void SetBitmask(const Utilities::BitMask<>& aBitmask);

		Transform* transform;

	private:
		std::string myName = "New Gameobject";

		int myID = -1;
		Utilities::BitMask<> myBitmask;

		std::vector<std::type_index> myDirtyComponents;
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