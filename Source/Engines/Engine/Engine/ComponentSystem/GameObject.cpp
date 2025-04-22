#include "GameObject.h"

#include <Engine/Utilities/Random.hpp>
#include "GameObjectManager.h"

namespace Zengine::ComponentSystem
{
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
}