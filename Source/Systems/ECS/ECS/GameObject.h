#pragma once

namespace Zengine
{
	namespace ComponentSystem
	{
		class IComponent;
		class GameObject
		{
			friend class GameObjectManager;

		public:
			IComponent* AddComponent();
			IComponent* GetComponent();

			const size_t& GetID();

		private:
			size_t id;
		};
	}

	namespace CS = ComponentSystem;
}
