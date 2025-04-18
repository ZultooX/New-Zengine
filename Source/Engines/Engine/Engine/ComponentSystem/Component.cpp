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

	void Component::SetID(const int& aId)
	{
		myId = aId;
	}

	const int& Component::GetID() const
	{
		return myId;
	}
}