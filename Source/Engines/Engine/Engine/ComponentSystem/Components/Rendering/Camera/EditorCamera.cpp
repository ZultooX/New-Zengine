#include "EditorCamera.h"

#include <Engine/Editor/DebugLogger.h>
#include <Zultools/InputManager.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>

#include <Zultools/Timer.h>
#include <Engine/Utilities/MainSingleton.h>
#include <Engine/Editor/DebugLogger.h>
#include <ImGui/imgui.h>

namespace Zengine::ComponentSystem
{
	void EditorCamera::Update()
	{
		if (InputManager::GetInstance()->GetMouseButton(MouseButton::Right))
		{
			HandleMovement();
			HandleLookAround();
		}
		else
		{
			HandleNonMovement();
		}

		Camera::Update();
	}

	void EditorCamera::HandleNonMovement()
	{
		POINT point = InputManager::GetInstance()->GetMousePosition();

		lastPosition = Vector2i((int)point.x, (int)point.y);
	}

	void EditorCamera::HandleLookAround()
	{
		POINT point = InputManager::GetInstance()->GetMousePosition();

		int deltaX = (int)point.x - lastPosition.x;
		int deltaY = (int)point.y - lastPosition.y;

		Vector3f rot = gameobject->transform->GetEulerAngles();

		rot.x += deltaY * 0.003f;
		rot.y += deltaX * 0.003f;

		gameobject->transform->SetEulerAngles(rot);

		lastPosition = Vector2i((int)point.x, (int)point.y);
	}

	void EditorCamera::HandleMovement()
	{
		float deltaTime = MainSingleton::GetInstance<CommonUtilities::Timer>().GetDeltaTime();

		float x = InputManager::GetInstance()->GetKey(KeyCode::D) - InputManager::GetInstance()->GetKey(KeyCode::A);
		float y = InputManager::GetInstance()->GetKey(KeyCode::E) - InputManager::GetInstance()->GetKey(KeyCode::Q);
		float z = InputManager::GetInstance()->GetKey(KeyCode::W) - InputManager::GetInstance()->GetKey(KeyCode::S);

		Vector3f movement = (gameobject->transform->GetRight() * x) +
			(gameobject->transform->GetUp() * y) +
			(gameobject->transform->GetForward() * z);


		float speedMultiplier = 1;

		if (InputManager::GetInstance()->GetKey(KeyCode::SHIFT))
		{
			speedMultiplier += SpaceMoveSpeedMultiplier;
		}

		Vector3f pos = gameobject->transform->GetPosition();
		 pos+= movement * deltaTime * speedMultiplier * myMovementSpeedMultiplier;
		 gameobject->transform->SetPosition(pos);
	}
}