#pragma once

#include <unordered_map>
#include <vector>
#include "GameObject.h"

namespace Zengine::ComponentSystem
{
	class GameObjectManager final
	{
	public:
		static void BeginFrame();

	public:
		static GameObject* CreateGameObject();
		static GameObject* CreateGameObject(const int& aId);

		static GameObject* GetGameObject(const int& aId);
		static std::unordered_map<int, GameObject*>& GetGameObjects() ;

		static void DestroyGameObject(const int& aId);

	private:
		static std::unordered_map<int, GameObject*> myIdToGameObject;
		static std::vector<std::string> Names;
	};
}

namespace CS = Zengine::ComponentSystem;