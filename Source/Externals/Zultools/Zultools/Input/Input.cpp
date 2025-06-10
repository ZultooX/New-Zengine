#include "Input.h"

#include <windowsx.h>
#include <unordered_map>

GamepadManager Input::gamepadManager;

int Input::myScrollDelta = 0;

bool Input::myMouseIsInside = false;
bool Input::myWindowIsFocused = false;
bool Input::myIsTrackingMouse = false;

Vector2i Input::myCurrentMousePos = Vector2i();
Vector2i Input::myMouseDeltaPos = Vector2i();

std::bitset<256> Input::myCurrentKey;
std::bitset<256> Input::myLastKey;
std::bitset<256> Input::myPressedThisFrame;
std::bitset<256> Input::myReleasedThisFrame;

std::unordered_map<std::string, Axis> Input::myAxis;

GamepadManager& Input::GetGamepadManager() { return gamepadManager; }

void Input::Initialize()
{
	gamepadManager.Initialize();

	RegisterAxis("Horizontal", Keycode::A, Keycode::D);
	RegisterAxis("Vertical", Keycode::S, Keycode::W);
}

void Input::Update()
{
	gamepadManager.Update();

	myPressedThisFrame = myCurrentKey & ~myLastKey;
	myReleasedThisFrame = ~myCurrentKey & myLastKey;

	myLastKey = myCurrentKey;
}

void Input::ProcessMessage(const HWND& aHwnd, const UINT& aMessage, const WPARAM& aWparam, const LPARAM& aLparam)
{
	myScrollDelta = 0;

	switch (aMessage)
	{
	case WM_SETFOCUS:		HandleFocus(true); break;
	case WM_KILLFOCUS:		HandleFocus(false); break;

	case WM_MOUSELEAVE:		HandleMouseLeave(); break;

	case WM_MOUSEHWHEEL:	HandleScroll(aWparam);  break;
	case WM_MOUSEWHEEL:		HandleScroll(aWparam); break;

	case WM_MOUSEMOVE:		HandleMouseMove(aHwnd, aLparam); break;

	case WM_RBUTTONUP:		HandleMouseButtonUp(Keycode::RightMouseButton); break;
	case WM_LBUTTONUP:		HandleMouseButtonUp(Keycode::LeftMouseButton); break;
	case WM_MBUTTONUP:		HandleMouseButtonUp(Keycode::MiddleMouseButton); break;

	case WM_RBUTTONDOWN:	HandleMouseButtonDown(Keycode::RightMouseButton); break;
	case WM_LBUTTONDOWN:	HandleMouseButtonDown(Keycode::LeftMouseButton); break;
	case WM_MBUTTONDOWN:	HandleMouseButtonDown(Keycode::MiddleMouseButton); break;

	case WM_XBUTTONUP:		HandleXButton(aWparam, false); break;
	case WM_XBUTTONDOWN:	HandleXButton(aWparam, true); break;


	case WM_KEYUP:			HandleKeyboardKeyUp(aWparam); break;
	case WM_KEYDOWN:		HandleKeyboardKeyDown(aWparam); break;
	}
}

int Input::GetKey(const Keycode& aKeycode)
{
	return myCurrentKey[(int)aKeycode] ? 1 : 0;
}

int Input::GetKey(const char& aKey)
{
	return myCurrentKey[(int)aKey] ? 1 : 0;
}



int Input::GetKeyDown(const Keycode& aKeycode)
{
	return myPressedThisFrame[(int)aKeycode] ? 1 : 0;
}

int Input::GetKeyDown(const char& aKey)
{
	return myPressedThisFrame[(int)aKey] ? 1 : 0;

}



int Input::GetKeyUp(const Keycode& aKeycode)
{
	return myReleasedThisFrame[(int)aKeycode] ? 1 : 0;
}

int Input::GetKeyUp(const char& aKey)
{
	return myReleasedThisFrame[(int)aKey] ? 1 : 0;
}


#pragma region [GET MOUSE BUTTON]

const int& Input::GetScrollDelta()
{
	return myScrollDelta;
}

const bool& Input::GetWindowFocus()
{
	return myWindowIsFocused;
}

const bool& Input::GetMouseInside()
{
	return myMouseIsInside;
}

#pragma endregion


#pragma region [AXIS]

void Input::RegisterAxis(const std::string& aName, const Keycode& aNegative, const Keycode& aPositive)
{
	myAxis[aName] = { aNegative, aPositive };
}

int Input::GetAxis(const std::string& aName)
{
	Axis axis = myAxis.at(aName);
	return Input::GetKey(axis.Positive) - Input::GetKey(axis.Negative);
}

#pragma endregion



#pragma region [HANDLE EVENTS]

void Input::HandleMouseLeave()
{
	myIsTrackingMouse = false;
	myMouseIsInside = false;
}

void Input::HandleMouseMove(const HWND& aHwnd, const LPARAM& aLparam)
{
	if (!myMouseIsInside) myMouseIsInside = true;

	int x = GET_X_LPARAM(aLparam);
	int y = GET_Y_LPARAM(aLparam);

	Vector2i newMousePos = Vector2i(x, y);

	myMouseDeltaPos = newMousePos - myCurrentMousePos;

	myCurrentMousePos = newMousePos;

	if (!myIsTrackingMouse)
	{
		TRACKMOUSEEVENT tme = {};
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = aHwnd;
		TrackMouseEvent(&tme);

		myIsTrackingMouse = true;
	}
}

void Input::HandleKeyboardKeyDown(const WPARAM& aWparam)
{
	myCurrentKey[aWparam] = true;
}

void Input::HandleKeyboardKeyUp(const WPARAM& aWparam)
{
	myCurrentKey[aWparam] = false;
}

void Input::HandleMouseButtonDown(const Keycode& aKeycode)
{
	myCurrentKey[(int)aKeycode] = true;
}

void Input::HandleMouseButtonUp(const Keycode& aKeycode)
{
	myCurrentKey[(int)aKeycode] = false;
}

void Input::HandleXButton(const WPARAM& aWparam, const bool& aButtonDown)
{
	const short pressedButton = GET_XBUTTON_WPARAM(aWparam);
	Keycode button;

	switch (pressedButton)
	{
	case XBUTTON1: button = Keycode::BackMouseButton; break;
	case XBUTTON2: button = Keycode::ForwardMouseButton; break;
	default: return;
	}

	if (aButtonDown) HandleMouseButtonDown(button);
	else HandleMouseButtonUp(button);
}


void Input::HandleScroll(const WPARAM& aWparam)
{
	const int scroll = GET_WHEEL_DELTA_WPARAM(aWparam);

	if (scroll > 0) myScrollDelta = 1;
	else if (scroll < 0) myScrollDelta = -1;
}

void Input::HandleFocus(const bool& aState)
{
	myWindowIsFocused = aState;
}

#pragma endregion