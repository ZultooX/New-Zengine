#include "Component.h"

#include <Engine/Objects/ComponentSystem/Base/ComponentData.h>
#include <Engine/Objects/ComponentSystem/GameObjectManager.h>
#include <fstream>

namespace Zengine
{
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

	void Component::SetID(const int& aId) { myId = aId; }
	const int& Component::GetID() const { return myId; }

	void Component::SetBit(const int& aBit, const bool& aState) { myMask.SetBit(aBit, aState); }
	bool Component::GetBit(const int& aBit) { return myMask.GetBit(aBit); }

	const std::string& Component::GetTypeName() const { return myName; }
	std::string& Component::GetTypeName() { return myName; }

	const std::type_index& Component::GetTypeIdx() const { return myType; }
	std::type_index& Component::GetTypeIdx() { return myType; }
}