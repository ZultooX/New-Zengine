#include "EditorCamera.h"

#include <Engine/Editor/DebugLogger.h>
#include <Zultools/InputManager.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>

#include <Zultools/Timer.h>
#include <Engine/Utilities/MainSingleton.h>
#include <Engine/Editor/DebugLogger.h>
#include <ImGui/imgui.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/Engine.h>
#include <Zultools/Input/InputMapper.h>
#include <Zultools/Input/Input.h>

namespace Zengine::ComponentSystem
{
	void EditorCamera::Start()
	{
		gameobject->AddComponent<Camera>();

		InputMapper& mapper = Engine::GetInputMapper();
		//mapper.Map({})
	}

	void EditorCamera::Update()
	{
		if (Input::GetKey(Keycode::RightMouseButton))
		{
			HandleMovement();
			HandleLookAround();
		}
		else
		{
			HandleNonMovement();
		}
	}

	const float& EditorCamera::GetMovementSpeedMultiplier() const { return myMovementSpeedMultiplier; }
	void EditorCamera::SetMovementSpeedMultiplier(const float& aMultiplier) { myMovementSpeedMultiplier = aMultiplier; }

	const float& EditorCamera::GetScrollMultiplier() const { return myMovementSpeedScrollMultiplier; }
	void EditorCamera::SetScrollMultiplier(const float& aMultiplier) { myMovementSpeedScrollMultiplier = aMultiplier; }


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

		float x = Input::GetAxis("Horizontal");
		float z = Input::GetAxis("Vertical");
		float y = InputManager::GetInstance()->GetKey(KeyCode::E) - InputManager::GetInstance()->GetKey(KeyCode::Q);

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