#include "GameObjectManager.h"

#include "GameObject.h"
#include<random>
#include<limits>

using namespace Zengine::ComponentSystem;

std::unordered_map<size_t, GameObject*> GameObjectManager::GameObjects;

GameObject* GameObjectManager::CreateGameObject()
{
    return CreateGameObject(GetRandomID());
}

GameObject* GameObjectManager::CreateGameObject(const size_t& aId)
{
    GameObject* obj = new GameObject();
    obj->id = aId;

    GameObjects[obj->id] = obj;

    return obj;
}

GameObject* GameObjectManager::GetGameObject()
{


    return nullptr;
}

size_t GameObjectManager::GetRandomID()
{
    size_t id = 0;
    while (GameObjects.find(id) != GameObjects.end())
    {
        std::random_device rd;
        std::mt19937 gen(rd);

        std::uniform_int_distribution<size_t> dist(std::numeric_limits<size_t>::min(), std::numeric_limits<size_t>::max());

        id = dist(gen);
    }

    return id;
}
