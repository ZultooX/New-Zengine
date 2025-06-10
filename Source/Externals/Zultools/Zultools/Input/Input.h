#pragma once

#include "Keycode.h"
#include <bitset>
#include <string>
#include "GamepadManager.h"
#include <unordered_map>
#include <Zultools/BitMask.hpp>
#include <Zultools/Math/Vector2.hpp>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct Axis {
	Keycode Negative;
	Keycode Positive;
};

class Input
{
	friend class Engine;

public:
	static GamepadManager& GetGamepadManager();

private:
	static void Initialize();
	static void Update();
	static void ProcessMessage(const HWND& aHwnd, const UINT& aMessage, const WPARAM& aWparam, const LPARAM& aLparam);

private:
	static void HandleMouseLeave();
	static void HandleMouseMove(const HWND& aHwnd, const LPARAM& aLparam);

	static void HandleKeyboardKeyDown(const WPARAM& aWparam);
	static void HandleKeyboardKeyUp(const WPARAM& aWparam);

	static void HandleMouseButtonDown(const Keycode& aKeycode);
	static void HandleMouseButtonUp(const Keycode& aKeycode);

	static void HandleXButton(const WPARAM& aWparam, const bool& aButtonDown);

	static void HandleScroll(const WPARAM& aWparam);

	static void HandleFocus(const bool& aState);

public:
#pragma region [GET KEY]

	/// <summary>																		
	/// Checks if the button is pressed.												
	/// </summary>																		
	/// <param name="aKeycode">The key pressed.</param>									
	/// <returns>Returns 0 if the button is up, 1 if the button is down.</returns>		
	static int GetKey(const Keycode& aKeycode);


	/// <summary>																		
	/// Checks if the button is pressed.												
	/// </summary>																		
	/// <param name="aKeycode">The key pressed.</param>									
	/// <returns>Returns 0 if the button is up, 1 if the button is down.</returns>		
	static int GetKey(const char& aKeycode);

#pragma endregion


#pragma region [GET KEY DOWN]

	/// <summary>
	///	Checks if the button was pressed this frame.
	/// </summary>
	/// <param name="aKeycode">The key pressed.</param>
	/// <returns>Returns 0 if the button is up, 1 if the button is down.</returns>
	static int GetKeyDown(const Keycode& aKeycode);


	/// <summary>
	///	Checks if the button was pressed this frame.
	/// </summary>
	/// <param name="aKeycode">The key pressed.</param>
	/// <returns>Returns 0 if the button is up, 1 if the button is down.</returns>
	static int GetKeyDown(const char& aKeycode);

#pragma endregion


#pragma region [GET KEY DOWN]

	/// <summary>
	/// Checks if the button was released this frame.
	/// </summary>
	/// <param name="aKeycode">The key pressed.</param>
	/// <returns>Returns 0 if the button is up, 1 if the button is down.</returns>
	static int GetKeyUp(const Keycode& aKeycode);


	/// <summary>
	/// Checks if the button was released this frame.
	/// </summary>
	/// <param name="aKeycode">The key pressed.</param>
	/// <returns>Returns 0 if the button is up, 1 if the button is down.</returns>
	static int GetKeyUp(const char& aKeycode);

#pragma endregion


#pragma region [MOUSE DATA]

	/// <summary>
	/// Gets the scroll wheel delta.
	/// </summary>
	/// <returns>1 or -1 depending on the direction of the scroll.</returns>
	static const int& GetScrollDelta();


	/// <summary>
	/// Checks if the window is in focus.
	/// </summary>
	/// <returns>Returns true or false if the window is in focus.</returns>
	static const bool& GetWindowFocus();


	/// <summary>
	/// Checks if the mouse is inside the window.
	/// </summary>
	/// <returns>Returns true or false if the mouse is inside.</returns>
	static const bool& GetMouseInside();

#pragma endregion


#pragma region [AXIS]

	static void RegisterAxis(const std::string& aName, const Keycode& aNegative, const Keycode& aPositive);

	static int GetAxis(const std::string& aName);

#pragma endregion



private:
	static GamepadManager gamepadManager;

private:
	static int myScrollDelta;

	static bool myMouseIsInside;
	static bool myWindowIsFocused;
	static bool myIsTrackingMouse;

	static Vector2i myCurrentMousePos;
	static Vector2i myMouseDeltaPos;

	static std::bitset<256> myCurrentKey;
	static std::bitset<256> myLastKey;
	static std::bitset<256> myPressedThisFrame;
	static std::bitset<256> myReleasedThisFrame;

	static std::unordered_map<std::string, Axis> myAxis;
};

