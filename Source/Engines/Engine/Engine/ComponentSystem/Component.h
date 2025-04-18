#pragma once

#include <Engine/Utilities/BitMask.hpp>

namespace Zengine::ComponentSystem
{
	class Component
	{
	public:
		//bool operator ==(const ComponentState& aState);
		//bool operator ==(const Component& aComp);

		//bool IsNull();

		void SetID(const int& aId);
		const int& GetID() const;

	private:
		Zengine::Util::BitMask<> myMask;
		int myId;
	};

}

namespace CS = Zengine::ComponentSystem;
