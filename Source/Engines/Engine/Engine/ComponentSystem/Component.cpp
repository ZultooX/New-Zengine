#include "Component.h"

namespace Zengine::ComponentSystem
{
	//bool Component::operator==(const ComponentState& aState)
	//{
	//	return myMask.GetBit(aState);
	//}

	//bool Component::operator==(const Component& aComp)
	//{
	//	return myId == aComp.myId;
	//}

	//bool Component::IsNull()
	//{
	//	return myMask.GetBit(ComponentState::NULL);
	//}

	Component::Component()
		: myMask(),
		myId(-1),
		myType(typeid(void))
	{
	}

	void Component::SetDirty()
	{
		SetBit(IsDirty, true);
		gameobject->AddDirtyComponent(myType);
	}

	void Component::ClearDirty()
	{
	}

	void Component::SetID(const int& aId)
	{
		myId = aId;
	}

	const int& Component::GetID() const
	{
		return myId;
	}
	void Component::SetBit(const int& aBit, const bool& aState)
	{
		myMask.SetBit(aBit, aState);
	}
	bool Component::GetBit(const int& aBit)
	{
		return myMask.GetBit(aBit);
	}
}