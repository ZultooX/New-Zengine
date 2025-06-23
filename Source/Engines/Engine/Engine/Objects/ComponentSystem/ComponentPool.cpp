#include "ComponentPool.h"

#include "GameObjectManager.h"


Zengine::ComponentSystem::GameObject* Zengine::ComponentSystem::IComponentPool::GetGameObject(const int& aGameObjID)
{
	return GameObjectManager::GetGameObject(aGameObjID);
}
