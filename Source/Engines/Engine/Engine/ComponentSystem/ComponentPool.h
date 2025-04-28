#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm> 

#include <Engine/Utilities/Random.hpp>
#include "ComponentStates.h"

namespace Zengine::ComponentSystem
{
	class GameObject;
	class Component;
	class IComponentPool {
	public:
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;

		virtual std::vector<Component*> GetComponent(const int& aId) = 0;

	protected:
		GameObject* GetGameObject(const int& aGameObjID);
	};

	template<typename T>
	class ComponentPool : public IComponentPool
	{
	public:
		void Awake() override;
		void Start() override;
		void Update() override;
		void LateUpdate() override;

	public:
		T* AddComponent(const int& aGameObjID);
		T* GetComponent(const int& aGameObjID, const int& aIdx = 0);
		std::vector<T*>& GetComponents();
		void RemoveComponent(const int& aGameObjID, const int& aIdx = 0);

		std::vector<Component*> GetComponent(const int& aId) override;


	private:
		std::unordered_map<int, int> myCompIdToIdx;
		std::unordered_map<int, std::vector<int>> myGameObjIdToCompIdList;
		std::vector<T*> myComponents;
	};


	template<typename T>
	inline void ComponentPool<T>::Awake()
	{
		for (T* comp : myComponents)
		{
			if (!comp->GetBit(ComponentStates::AWAKENED))
				comp->Awake();
		}
	}

	template<typename T>
	inline void ComponentPool<T>::Start()
	{
		for (T* comp : myComponents)
		{
			if (!comp->GetBit(ComponentStates::STARTED))
				comp->Start();
		}
	}

	template<typename T>
	inline void ComponentPool<T>::Update()
	{
		for (T* comp : myComponents)
		{
			comp->Update();
		}
	}

	template<typename T>
	inline void ComponentPool<T>::LateUpdate()
	{
		for (T* comp : myComponents)
		{
			comp->LateUpdate();
		}
	}

	template<typename T>
	inline T* ComponentPool<T>::AddComponent(const int& aGameObjID)
	{
		const int randomID = Random::GetValue<int>(INT_MIN, INT_MAX);

		T* comp = new T();
		comp->SetID(randomID);
		comp->gameobject =GetGameObject(aGameObjID) ;

		myGameObjIdToCompIdList[aGameObjID].push_back((int)myComponents.size());
		myCompIdToIdx[comp->GetID()] = (int)myComponents.size();

		myComponents.push_back(comp);

		return myComponents.back();
	}

	template<typename T>
	inline T* ComponentPool<T>::GetComponent(const int& aGameObjID, const int& aIdx)
	{
		const int& idx = myGameObjIdToCompIdList[aGameObjID][aIdx];

		return myComponents[aIdx];
	}

	template<typename T>
	inline std::vector<T*>& ComponentPool<T>::GetComponents()
	{
		return myComponents;
	}

	template<typename T>
	inline void ComponentPool<T>::RemoveComponent(const int& aGameObjID, const int& aIdx)
	{
		T* remove = myComponents[myGameObjIdToCompIdList[aGameObjID][aIdx]];
		int removeIdx = myCompIdToIdx[remove->GetID()];

		T* last = myComponents.back();
		int lastID = last->GetID();

		std::swap(myComponents[removeIdx], myComponents[myComponents.size() - 1]);

		myCompIdToIdx[lastID] = removeIdx;
		myCompIdToIdx.erase(remove->GetID());
		myGameObjIdToCompIdList[aGameObjID].erase(myGameObjIdToCompIdList[aGameObjID].begin() + aIdx);

		if (myGameObjIdToCompIdList[aGameObjID].empty())
		{
			myGameObjIdToCompIdList.erase(aGameObjID);
		}

		delete last;

		myComponents.pop_back();
	}
	template<typename T>
	inline std::vector<Component*> ComponentPool<T>::GetComponent(const int& aId)
	{
		if (myGameObjIdToCompIdList.find(aId) == myGameObjIdToCompIdList.end()) return {};


		std::vector<Component*> comps;

		for (const int& id : myGameObjIdToCompIdList.at(aId))
		{
			comps.push_back(myComponents[id]);
		}

		return comps;
	}
}

namespace CS = Zengine::ComponentSystem;