#pragma once
#include <Zultools/Math/Vector2.hpp>
#include <bitset>
#include "Keycode.h"
#include <Zultools/Math/Color.h>

enum class SupportFlags : int {
	HAPTICS,
	LED
};

class SDL_Haptic;
class SDL_Gamepad;
class SDL_Joystick;
class Gamepad
{
	friend class GamepadManager;
	friend class InputManagerWindow;

public:
	Gamepad() = default;
	Gamepad(const uint32_t& aID);

public:
	int GetButton(const GamepadButton& aGamepadButton);
	int GetButtonDown(const GamepadButton& aGamepadButton);
	int GetButtonUp(const GamepadButton& aGamepadButton);

	const float& GetRightTrigger() const;
	const float& GetLeftTrigger() const;

	const Vector2f& GetRightJoystick() const;
	const Vector2f& GetLeftJoystick() const;

	/// <summary>
	/// Vibrates the controller.
	/// </summary>
	/// <param name="aStrengthLeft"> | A strength on the left side.</param>
	/// <param name="aStrengthRight"> | A strength on the right side.</param>
	/// <param name="aDuration"> | A duration in milliseconds.</param>
	void PlayHaptic(const int& aStrengthLeft, const int& aStrengthRight, const float& duration);

public:
	void SetColor(const Color& aColor);

public:
	void Update();

private:
	float rightTrigger = 0;
	float leftTrigger = 0;

	std::bitset<32> flags;
	std::bitset<32> currentButtons;
	std::bitset<32> lastButtons;
	std::bitset<32> buttonPressedThisFrame;
	std::bitset<32> buttonReleasedThisFrame;

	Vector2f rightJoystick;
	Vector2f leftJoystick;

	Color currentColor;

	uint32_t id;
	SDL_Gamepad* gamepad;
	SDL_Joystick* joystick;
	SDL_Haptic* haptic;
};

