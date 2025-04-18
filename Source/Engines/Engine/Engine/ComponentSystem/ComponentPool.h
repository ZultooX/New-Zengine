#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm> 

#include <Engine/Utilities/Random.hpp>

namespace Zengine::ComponentSystem
{
	class IComponentPool{};

	template<typename T>
	class ComponentPool : public IComponentPool
	{
	public:
		T* AddComponent(const int& aGameObjID);
		T* GetComponent(const int& aGameObjID, const int& aIdx = 0);
		void RemoveComponent(const int& aGameObjID, const int& aIdx = 0);


	private:
		std::unordered_map<int, int> myCompIdToIdx;
		std::unordered_map<int, std::vector<int>> myGameObjIdToCompIdList;
		std::vector<T*> myComponents;
	};


	template<typename T>
	inline T* ComponentPool<T>::AddComponent(const int& aGameObjID)
	{
		const int randomID = Random::GetValue<int>();

		T* comp = new T;
		comp->SetID(randomID);

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
}