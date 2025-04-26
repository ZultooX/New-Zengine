#pragma once

#include <unordered_map>
#include "GameObject.h"

namespace Zengine::ComponentSystem
{
	class GameObjectManager final
	{
	public:
		static GameObject* CreateGameObject();
		static GameObject* CreateGameObject(const int& aId);

		static GameObject* GetGameObject(const int& aId);
		static std::unordered_map<int, GameObject*>& GetGameObjects() ;

		static void DestroyGameObject(const int& aId);

	private:
		static std::unordered_map<int, GameObject*> myIdToGameObject;
	};
}

namespace CS = Zengine::ComponentSystem;