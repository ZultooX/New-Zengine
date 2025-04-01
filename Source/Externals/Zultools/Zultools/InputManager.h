#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Keycode.h"

#include <bitset>
#include <assert.h>

extern HWND gHWND;

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;

	enum MouseLockMode
	{
		Restricted,
		Unrestricted,
		Confined,
		Unconfined
	};

	static InputManager* GetInstance();


public:
	void Update();
	bool UpdateEvents(UINT aMessage, WPARAM aWparam, LPARAM aLparam);

	bool GetKeyDown(KeyCode aKeyCode);
	bool GetKeyUp(KeyCode aKeyCode);
	bool GetKey(KeyCode aKeyCode);

	bool GetMouseButtonDown(const MouseButton& aMouseButton);
	bool GetMouseButtonUp(const MouseButton& aMouseButton);
	bool GetMouseButton(const MouseButton& aMouseButton);

	void ChangeMouseLockMode(const MouseLockMode& aMouseLockMode);

	POINT GetMousePosition();
	POINT GetMouseDeltaPosition();

	int GetScrollWheel();

	void SetMousePosition(const int& aXPos, const int& aYPos);
	void SetMousePositionNormalized(const float& aXPos, const float& aYPos);

	void ShowMyCursor(const bool& aIsVisible);


private:
	POINT myCurrentCursorPosition;
	POINT myLastCursorPosition;

	std::bitset<256> myCurrentKey;
	std::bitset<256> myLastKey;

	bool myM_MouseButtonCurrentState = false;
	bool myM_MouseButtonLastState = false;

	bool myL_MouseButtonCurrentState = false;
	bool myL_MouseButtonLastState = false;

	bool myR_MouseButtonCurrentState = false;
	bool myR_MouseButtonLastState = false;

	bool myMouseConfinedInCenter = false;

	int myScrollWheelDeltaZ = 0;
};