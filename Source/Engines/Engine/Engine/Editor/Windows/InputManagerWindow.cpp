#include "InputManagerWindow.h"

#include <Zultools/Random.h>
#include <Zultools/Input/GamepadManager.h>
#include <Zultools/Input/Input.h>
#include <imgui.h>

InputManagerWindow::InputManagerWindow(const int& aId)
{
	myWindowName = "Input Manager";
	myID = aId == -1 ? Random::GetValue<int>() : aId;
}

void InputManagerWindow::Open()
{
}

void InputManagerWindow::Update()
{
	GamepadManager& manager = Input::GetGamepadManager();

	const int& connectedGamepads = manager.GetConnectedGamepadAmount();

	for (int i = 0; i < manager.GetConnectedGamepadAmount(); ++i)
	{
		if (ImGui::Button(std::to_string(i + 1).c_str(), { 100, 100 }))
		{
			myActiveGamepad = i;
		}
	}

	if (myActiveGamepad > -1)
	{
		Uint32 id = manager.GetIDs()[myActiveGamepad];

		Gamepad& pad = manager.GetPad(id);
		for (int i = 0; i < (int)GamepadButton::MISC6; ++i)
		{
			if (pad.GetButton((GamepadButton)i))
			{
				ImGui::Text(std::to_string(i).c_str());
			}
		}

		if (ImGui::Button("Haptic")) pad.PlayHaptic(400000, 400000, 2000);

		float rightTrigger = pad.GetRightTrigger();
		float leftTrigger = pad.GetLeftTrigger();
		Vector2f left = pad.GetLeftJoystick();
		Vector2f right = pad.GetRightJoystick();
		ImGui::DragFloat2("Left Joy", &left.x);
		ImGui::DragFloat2("Right Joy", &right.x);

		ImGui::DragFloat("Left", &leftTrigger);
		ImGui::DragFloat("Right", &rightTrigger);

		static Color col = {};
		ImGui::ColorPicker3("Color", &col.r);
		pad.SetColor(col);
	}

	ImGui::Text(("Connected gamepads: " + std::to_string(manager.GetConnectedGamepadAmount())).c_str());



}

void InputManagerWindow::Close()
{
}
