#include "GameObject.h"

#include <Engine/Utilities/Random.hpp>
#include "GameObjectManager.h"

namespace Zengine::ComponentSystem
{
	void GameObject::NewFrame()
	{
		if (!myDirtyComponents.empty())
		{
			myDirtyComponents.clear();
		}
	}

	GameObject* GameObject::Create()
	{
		return GameObjectManager::CreateGameObject();
	}
	
	GameObject* GameObject::Create(const int& aId)
	{
		return GameObjectManager::CreateGameObject(aId);
	}

	GameObject::~GameObject()
	{
		GameObjectManager::DestroyGameObject(myID);
	}

	void GameObject::SetID(const int aId)
	{
		myID = aId;
	}
	void GameObject::SetName(std::string aName)
	{
		myName = aName;
	}
	void GameObject::AddDirtyComponent(const std::type_index& aType)
	{
		myDirtyComponents.push_back(aType);
	}
	const std::vector<std::type_index>& GameObject::GetDirtyComponents() const
	{
		return myDirtyComponents;
	}
	const Utilities::BitMask<>& GameObject::GetBitmask() const { return myBitmask; }
	Utilities::BitMask<>& GameObject::GetBitmask() { return myBitmask; }

	void GameObject::SetBitmask(const Utilities::BitMask<>& aBitmask)
	{
		myBitmask = aBitmask;
	}
}