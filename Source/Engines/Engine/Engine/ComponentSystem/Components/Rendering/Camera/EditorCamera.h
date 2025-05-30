#pragma once

#include <Engine/ComponentSystem/Component.h>
#include <Zultools/Math/Vector2.hpp>

namespace Zengine::ComponentSystem
{
	class EditorCamera : public Component
	{
		COMPONENT_BASICS(EditorCamera)
		friend class InspectorWindow;

	public:
		void Start() override;
		void Update() override;


	private:
		void HandleNonMovement();
		void HandleLookAround();
		void HandleMovement();

	private:
		float myMovementSpeedScrollMultiplier = 1.f;
		float myMovementSpeedMultiplier = 3.f;
		Vector2i lastPosition = {};

		const float SpaceMoveSpeedMultiplier = 4.f;
	};
}