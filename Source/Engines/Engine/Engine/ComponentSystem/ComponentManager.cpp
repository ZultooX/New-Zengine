#include "ComponentManager.h"

namespace Zengine::ComponentSystem
{
	std::unordered_map<std::type_index, int> ComponentManager::myGameObjectIdToIdx;
	std::vector<IComponentPool*> ComponentManager::myComponentPools;
	void ComponentManager::Awake()
	{
		for (IComponentPool* pool : myComponentPools)
		{
			pool->Awake();
		}
	}
	void ComponentManager::Start()
	{
		for (IComponentPool* pool : myComponentPools)
		{
			pool->Start();
		}
	}

	void ComponentManager::Update()
	{
		for (IComponentPool* pool : myComponentPools)
		{
			pool->Update();
		}
	}
	
	void ComponentManager::LateUpdate()
	{
		for (IComponentPool* pool : myComponentPools)
		{
			pool->LateUpdate();
		}
	}

	void ComponentManager::UpdateManager()
	{
		Awake();
		Start();
		Update();
		LateUpdate();
	}
}