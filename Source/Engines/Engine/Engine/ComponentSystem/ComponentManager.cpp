#include "ComponentManager.h"

namespace Zengine::ComponentSystem
{
	std::unordered_map<std::type_index, int> ComponentManager::myGameObjectIdToIdx;
	std::vector<IComponentPool*> ComponentManager::myComponentPools;
}