#pragma once

#include <Engine/Utilities/BitMask.hpp>

#include "GameObject.h"
#include <typeindex>

#define COMP(ComponentType)							\
	public: \
ComponentType() : Component() { myType = typeid(Transform); } \
~ComponentType() override = default; \

namespace Zengine::ComponentSystem
{
	enum BitFlags
	{
		IsDirty = 0,

		EditorDrawn = 12,
	};


	class GameObject;
	class Component
	{
	public:
		Component();
		virtual ~Component() = default;

	public:
		virtual void Awake() { __noop; }
		virtual void Start() { __noop; }
		virtual void Update() { __noop; }
		virtual void LateUpdate() { __noop; }

		void SetDirty();
		void ClearDirty();

	public:
		void SetID(const int& aId);
		const int& GetID() const;

		void SetBit(const int& aBit, const bool& aState);
		bool GetBit(const int& aBit);

		GameObject* gameobject;

	protected:
		Zengine::Util::BitMask<> myMask;
		int myId;
		std::type_index myType;
	};

}

namespace CS = Zengine::ComponentSystem;
