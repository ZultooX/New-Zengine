#pragma once

#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Zultools/Math/Vector2.hpp>

namespace Zengine::ComponentSystem
{
	class EditorCamera : public Camera
	{
		friend class InspectorWindow;

	public:
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