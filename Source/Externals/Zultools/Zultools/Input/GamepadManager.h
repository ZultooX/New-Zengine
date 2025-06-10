#pragma once

#include <unordered_map>
#include <vector>
#include <limits>
#include "Gamepad.h"

#include <SDL3/SDL_events.h>

class GamepadManager
{
public:
	void Initialize();
	void Update();

public:
	Gamepad& GetPad(const int& aId);
	const int& GetConnectedGamepadAmount() const;

	const std::vector<Uint32>& GetIDs();


private:
	void HandleOnGamepadConnect(const SDL_Event& anEvent);
	void HandleOnGamepadDisconnect(const SDL_Event& anEvent);

	void HandleOnGamepadButtonDown(const SDL_Event& anEvent);
	void HandleOnGamepadButtonUp(const SDL_Event& anEvent);

	void HandleOnGamepadAxis(const SDL_Event& anEvent);


private:
	template<typename T>
	float Normalize(const T& value);

private:
	std::unordered_map<Uint32, Gamepad> idToGamepad;
	std::vector<Uint32> ids;

	int myConnectedGamepads = 0;
};

template<typename T>
inline float GamepadManager::Normalize(const T& value)
{
	constexpr T minVal = -32768;	
	constexpr T maxVal = 32767;
	float numerator = (float)value - (float)minVal;
	float denumerator = (float)maxVal - (float)minVal;
	float val = numerator / denumerator;

	return val * 2.f - 1.f;
}
