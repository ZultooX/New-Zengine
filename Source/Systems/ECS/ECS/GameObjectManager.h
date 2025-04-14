#pragma once

#include <unordered_map>

namespace Zengine
{
	namespace ComponentSystem
	{
		class GameObject;
		class GameObjectManager
		{
		public:
			static GameObject* CreateGameObject();
			static GameObject* CreateGameObject(const size_t& aId);

			static GameObject* GetGameObject();

		private:
			static size_t GetRandomID();

		private:
			static std::unordered_map<size_t, GameObject*> GameObjects;
		};
	}

	namespace CS = ComponentSystem;
}