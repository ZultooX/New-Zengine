#pragma once

#include <Engine/Utilities/BitMask.hpp>

#include "GameObject.h"
#include <typeindex>
#include <string>
#include <Engine/ComponentSystem/Base/ComponentData.h>

#define COMPONENT_BASICS(ComponentType)											\
public:																\
friend class SceneExporter; \
	ComponentType() : Component() { myName = #ComponentType; myType = typeid(ComponentType); }	\
	~ComponentType() override = default;							

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

		const std::string& GetTypeName() const;
		std::string& GetTypeName();

		const std::type_index& GetTypeIdx() const;
		std::type_index& GetTypeIdx();

		GameObject* gameobject;

	protected:
		Zengine::Util::BitMask<> myMask;
		int myId;
		std::type_index myType;
		std::string myName = "";
	};

}

namespace CS = Zengine::ComponentSystem;
