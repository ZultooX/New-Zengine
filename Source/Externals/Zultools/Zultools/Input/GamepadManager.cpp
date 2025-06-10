#include "GamepadManager.h"

#include <SDL3/SDL.h>
#include <iostream>

void GamepadManager::Initialize()
{
	SDL_Init(SDL_INIT_GAMEPAD | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC);

	int num_joysticks;
	SDL_JoystickID* joysticks = SDL_GetJoysticks(&num_joysticks);

	SDL_Gamepad* gamepad = nullptr;
	for (int i = 0; i < num_joysticks; ++i)
	{
		SDL_JoystickID id = joysticks[i];
		if (SDL_IsGamepad(id))
		{
			gamepad = SDL_OpenGamepad(id);
			if (gamepad)
			{
				idToGamepad[id] = Gamepad(id);
			}
		}
	}
}

void GamepadManager::Update()
{
	for (auto& [id, pad] : idToGamepad)
	{
		pad.Update();
	}

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_GAMEPAD_ADDED: HandleOnGamepadConnect(event); break;
		case SDL_EVENT_GAMEPAD_REMOVED: HandleOnGamepadDisconnect(event); break;

		case SDL_EVENT_GAMEPAD_BUTTON_DOWN: HandleOnGamepadButtonDown(event); break;
		case SDL_EVENT_GAMEPAD_BUTTON_UP: HandleOnGamepadButtonUp(event); break;

		case SDL_EVENT_GAMEPAD_AXIS_MOTION: HandleOnGamepadAxis(event); break;

		default:
			break;
		}
	}
}

void GamepadManager::HandleOnGamepadConnect(const SDL_Event& anEvent)
{
	const SDL_JoystickID& id = anEvent.gdevice.which;
	SDL_OpenGamepad(id);
	idToGamepad[id] = Gamepad(id);
	ids.push_back(id);
	++myConnectedGamepads;
}

void GamepadManager::HandleOnGamepadDisconnect(const SDL_Event& anEvent)
{
	const SDL_JoystickID& id = anEvent.gdevice.which;

	for (int i = 0; i < (int)ids.size(); ++i)
	{
		if (ids[i] == id)
		{
			ids.erase(ids.begin() + i);
			return;
		}
	}

	SDL_Gamepad* pad = SDL_GetGamepadFromID(id);
	SDL_CloseGamepad(pad);
	idToGamepad.erase(id);
	--myConnectedGamepads;
}

void GamepadManager::HandleOnGamepadButtonDown(const SDL_Event& anEvent)
{
	SDL_GamepadButton button = (SDL_GamepadButton)anEvent.gbutton.button;
	Gamepad& pad = idToGamepad.at(anEvent.gdevice.which);
	pad.currentButtons[(int)button] = true;
}

void GamepadManager::HandleOnGamepadButtonUp(const SDL_Event& anEvent)
{
	SDL_GamepadButton button = (SDL_GamepadButton)anEvent.gbutton.button;
	Gamepad& pad = idToGamepad.at(anEvent.gdevice.which);
	pad.currentButtons[(int)button] = false;
}

void GamepadManager::HandleOnGamepadAxis(const SDL_Event& anEvent)
{
	const SDL_JoystickID& id = anEvent.gdevice.which;
	Gamepad& pad = idToGamepad[id];

	switch (anEvent.gaxis.axis)
	{
	case SDL_GAMEPAD_AXIS_LEFTX: pad.leftJoystick.x = Normalize(anEvent.gaxis.value); break;
	case SDL_GAMEPAD_AXIS_LEFTY: pad.leftJoystick.y = Normalize(anEvent.gaxis.value); break;

	case SDL_GAMEPAD_AXIS_RIGHTX: pad.rightJoystick.x = Normalize(anEvent.gaxis.value); break;
	case SDL_GAMEPAD_AXIS_RIGHTY: pad.rightJoystick.y = Normalize(anEvent.gaxis.value); break;

	case SDL_GAMEPAD_AXIS_LEFT_TRIGGER: pad.leftTrigger = Normalize(anEvent.gaxis.value); break;
	case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER: pad.rightTrigger = Normalize(anEvent.gaxis.value); break;
	}
}

const std::vector<Uint32>& GamepadManager::GetIDs() { return ids; }

const int& GamepadManager::GetConnectedGamepadAmount() const { return myConnectedGamepads; }
Gamepad& GamepadManager::GetPad(const int& aId)
{
	return idToGamepad[aId];
}