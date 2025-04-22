#pragma once

#include <Engine/Utilities/BitMask.hpp>

#include "GameObject.h"

namespace Zengine::ComponentSystem
{

	class GameObject;
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		//bool operator ==(const ComponentState& aState);
		//bool operator ==(const Component& aComp);

		//bool IsNull();

	public:
		virtual void Awake() { __noop; }
		virtual void Start() { __noop; }
		virtual void Update() { __noop; }
		virtual void LateUpdate() { __noop; }

	public:
		void SetID(const int& aId);
		const int& GetID() const;

		void SetBit(const int& aBit, const bool& aState);
		bool GetBit(const int& aBit);

		GameObject* gameobject;

	private:
		Zengine::Util::BitMask<> myMask;
		int myId;
	};

}

namespace CS = Zengine::ComponentSystem;
