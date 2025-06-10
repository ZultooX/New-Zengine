#include "Gamepad.h"

#include <SDL3/SDL.h>


void Gamepad::Update()
{
	buttonPressedThisFrame = currentButtons & ~lastButtons;
	buttonReleasedThisFrame = ~currentButtons & lastButtons;

	lastButtons = currentButtons;
}


Gamepad::Gamepad(const uint32_t& aID) : id(aID)
{
	gamepad = SDL_GetGamepadFromID(id);

	if (SDL_RumbleGamepad(gamepad, 0, 0, 0)) flags.set((int)SupportFlags::HAPTICS, true);
	if(SDL_SetGamepadLED(gamepad, 255, 255, 255)) flags.set((int)SupportFlags::LED, true);
}

int Gamepad::GetButton(const GamepadButton& aGamepadButton)
{
	return currentButtons[(int)aGamepadButton] ? 1 : 0;
}

int Gamepad::GetButtonDown(const GamepadButton& aGamepadButton)
{
	return buttonPressedThisFrame[(int)aGamepadButton] ? 1 : 0;
}

int Gamepad::GetButtonUp(const GamepadButton& aGamepadButton)
{
	return buttonReleasedThisFrame[(int)aGamepadButton] ? 1 : 0;
}

const float& Gamepad::GetRightTrigger() const { return rightTrigger; }
const float& Gamepad::GetLeftTrigger() const { return leftTrigger; }

const Vector2f& Gamepad::GetRightJoystick() const { return rightJoystick; }
const Vector2f& Gamepad::GetLeftJoystick() const { return leftJoystick; }

void Gamepad::PlayHaptic(const int& aStrengthLeft, const int& aStrengthRight, const float& aDuration)
{
	if (!flags.test((int)SupportFlags::HAPTICS)) return;

	SDL_RumbleGamepad(gamepad, aStrengthLeft, aStrengthRight, aDuration);
}

void Gamepad::SetColor(const Color& aColor)
{
	if (!flags.test((int)SupportFlags::LED)) return;

	currentColor = aColor;
	SDL_SetGamepadLED(gamepad, currentColor.r * 255, currentColor.g * 255, currentColor.b * 255);
}
