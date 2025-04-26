#include "GameObjectManager.h"

#include <Engine/Utilities/Random.hpp>
#include <Engine/ComponentSystem/Components/TransformComponent.h>

namespace Zengine::ComponentSystem
{
    std::unordered_map<int, GameObject*> GameObjectManager::myIdToGameObject;

    GameObject* GameObjectManager::CreateGameObject()
    {
        const int id = Zengine::Random::GetValue<int>(INT_MIN, INT_MAX);

        return CreateGameObject(id);
    }

    GameObject* GameObjectManager::CreateGameObject(const int& aId)
    {
        myIdToGameObject[aId] = new GameObject();
        myIdToGameObject[aId]->SetID(aId);

        myIdToGameObject[aId]->transform = myIdToGameObject[aId]->AddComponent<Transform>();
        return myIdToGameObject[aId];
    }

    GameObject* GameObjectManager::GetGameObject(const int& aId)
    {
        return myIdToGameObject[aId];
    }

    std::unordered_map<int, GameObject*>& GameObjectManager::GetGameObjects()
    {
        return myIdToGameObject;
    }

    void GameObjectManager::DestroyGameObject(const int& aId)
    {
        delete myIdToGameObject[aId];
        myIdToGameObject.erase(aId);
    }
}
