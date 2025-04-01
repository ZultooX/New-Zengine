#include "InputManager.h"

InputManager* InputManager::GetInstance()
{
	static InputManager* Instance;
	if (Instance == nullptr) Instance = new InputManager;
	return Instance;
}

bool InputManager::GetKeyDown(KeyCode aKeyCode)
{
	int keyCode = static_cast<int>(aKeyCode);

	bool wasPressed = (myCurrentKey[keyCode] && !myLastKey[keyCode]);
	if (wasPressed)
	{
		myLastKey[keyCode] = true;
	}
	return wasPressed;
}

bool InputManager::GetKeyUp(KeyCode aKeyCode)
{
	int keyCode = static_cast<int>(aKeyCode);

	bool wasPressed = (!myCurrentKey[keyCode] && myLastKey[keyCode]);
	if (wasPressed)
	{
		myLastKey[keyCode] = false;
	}
	return wasPressed;
}

bool InputManager::GetKey(KeyCode aKeyCode)
{
	int keyCode = static_cast<int>(aKeyCode);

	if (myCurrentKey[keyCode])
	{

	}

	return myCurrentKey[keyCode];
}







void InputManager::Update()
{
	myLastCursorPosition = myCurrentCursorPosition;
	GetCursorPos(&myCurrentCursorPosition);

	ScreenToClient(gHWND, &myCurrentCursorPosition);

	if (myMouseConfinedInCenter)
	{
		SetMousePositionNormalized(0.5f, 0.5f);
	}
}

bool InputManager::UpdateEvents(UINT aMessage, WPARAM aWparam, LPARAM aLparam)
{
	UNREFERENCED_PARAMETER(aLparam);

	switch (aMessage)
	{
#pragma region Mouse
		// Scroll wheel. 
	case WM_MOUSEHWHEEL:
	case WM_MOUSEWHEEL:
	{
		int scrollDelta = GET_WHEEL_DELTA_WPARAM(aWparam);
		myScrollWheelDeltaZ += scrollDelta;
	}


	// Left mouse button.
	case WM_LBUTTONDOWN:
	{
		myL_MouseButtonLastState = myL_MouseButtonCurrentState;
		myL_MouseButtonCurrentState = true;
		return true;
	}
	case WM_LBUTTONUP:
	{
		myL_MouseButtonLastState = myL_MouseButtonCurrentState;
		myL_MouseButtonCurrentState = false;
		return true;
	}


	// Right mouse button.
	case WM_RBUTTONDOWN:
	{
		myR_MouseButtonLastState = myR_MouseButtonCurrentState;
		myR_MouseButtonCurrentState = true;
		return true;
	}

	case WM_RBUTTONUP:
	{
		myR_MouseButtonLastState = myR_MouseButtonCurrentState;
		myR_MouseButtonCurrentState = false;
		return true;
	}


	// Middle mouse button.
	case WM_MBUTTONDOWN:
	{
		myM_MouseButtonLastState = myM_MouseButtonCurrentState;
		myM_MouseButtonCurrentState = true;
		return true;
	}

	case WM_MBUTTONUP:
	{
		myM_MouseButtonLastState = myM_MouseButtonCurrentState;
		myM_MouseButtonCurrentState = false;
		return true;
	}
#pragma endregion

#pragma region Keyboard
	case WM_KEYUP:
	{
		myLastKey = myCurrentKey;
		myCurrentKey[aWparam] = false;

		return true;
	}

	case WM_KEYDOWN:
	{
		myLastKey = myCurrentKey;
		myCurrentKey[aWparam] = true;
		return true;
	}
#pragma endregion
	}

	return false;
}


bool InputManager::GetMouseButtonDown(const MouseButton& aMouseButton)
{
	switch (aMouseButton)
	{
	case MouseButton::Left:
	{
		bool wasPressed = (myL_MouseButtonCurrentState && !myL_MouseButtonLastState);
		if (wasPressed)
		{
			myL_MouseButtonLastState = true;
		}
		return wasPressed;
	}
	case MouseButton::Middle:
	{
		bool wasPressed = (myM_MouseButtonCurrentState && !myM_MouseButtonLastState);
		if (wasPressed)
		{
			myM_MouseButtonLastState = true;
		}
		return wasPressed;
	}
	case MouseButton::Right:
	{
		bool wasPressed = (myR_MouseButtonCurrentState && !myR_MouseButtonLastState);
		if (wasPressed)
		{
			myR_MouseButtonLastState = true;
		}
		return wasPressed;
	}
	default:
	{
		assert(false && "Invalid mouse button.");
		return false;
	}
	}
}


bool InputManager::GetMouseButtonUp(const MouseButton& aMouseButton)
{
	switch (aMouseButton)
	{
	case MouseButton::Left:
	{
		bool wasPressed = (!myL_MouseButtonCurrentState && myL_MouseButtonLastState);
		if (wasPressed)
		{
			myL_MouseButtonLastState = false;
		}
		return wasPressed;
	}
	case MouseButton::Middle:
	{
		bool wasPressed = (!myM_MouseButtonCurrentState && myM_MouseButtonLastState);
		if (wasPressed)
		{
			myM_MouseButtonLastState = false;
		}
		return wasPressed;
	}
	case MouseButton::Right:
	{
		bool wasPressed = (!myR_MouseButtonCurrentState && myR_MouseButtonLastState);
		if (wasPressed)
		{
			myR_MouseButtonLastState = false;
		}
		return wasPressed;
	}
	default:
	{
		assert(false && "Invalid mouse button.");
		return false;
	}
	}
}

bool InputManager::GetMouseButton(const MouseButton& aMouseButton)
{
	switch (aMouseButton)
	{
	case MouseButton::Left:
	{
		return myL_MouseButtonCurrentState;
	}
	case MouseButton::Middle:
	{
		return myM_MouseButtonCurrentState;
	}
	case MouseButton::Right:
	{
		return myR_MouseButtonCurrentState;
	}
	default:
	{
		assert("Invalid mouse button.");
		break;
	}
	}

	return false;
}

void InputManager::ChangeMouseLockMode(const MouseLockMode& aMouseLockMode)
{
	switch (aMouseLockMode)
	{
	case MouseLockMode::Restricted:
	{
		RECT r;
		GetWindowRect(gHWND, &r);
		ClipCursor(&r);
		break;
	}
	case MouseLockMode::Unrestricted:
	{
		ClipCursor(NULL);
		break;
	}
	case MouseLockMode::Confined:
	{
		myMouseConfinedInCenter = true;
		break;
	}
	case MouseLockMode::Unconfined:
	{
		myMouseConfinedInCenter = false;
		break;
	}
	default:
	{
		assert(false && "Invalid lock mode.");
		break;
	}
	}
}

POINT InputManager::GetMousePosition()
{
	return myCurrentCursorPosition;
}

POINT InputManager::GetMouseDeltaPosition()
{
	POINT mouseDelta;
	mouseDelta.x = myCurrentCursorPosition.x - myLastCursorPosition.x;
	mouseDelta.y = myCurrentCursorPosition.y - myLastCursorPosition.y;

	return mouseDelta;
}

int InputManager::GetScrollWheel()
{
	return myScrollWheelDeltaZ;
}

void InputManager::SetMousePosition(const int& aXPos, const int& aYPos)
{
	RECT rect;
	GetClientRect(gHWND, &rect);

	POINT targetPos = { rect.left + aXPos, rect.top + aYPos };

	ClientToScreen(gHWND, &targetPos);
	SetCursorPos(targetPos.x, targetPos.y);
}

void InputManager::SetMousePositionNormalized(const float& aXPos, const float& aYPos)
{
	assert((aXPos <= 1 && aXPos >= 0) && "Mouse is outside of range. Must be 0 - 1.");
	assert((aYPos <= 1 && aYPos >= 0) && "Mouse is outside of range. Must be 0 - 1.");

	RECT rect;
	GetClientRect(gHWND, &rect);

	float x = aXPos * rect.right;
	float y = aYPos * rect.bottom;

	POINT targetPos = { static_cast<LONG>(rect.left + x), static_cast<LONG>(rect.top + y) };

	ClientToScreen(gHWND, &targetPos);
	SetCursorPos(targetPos.x, targetPos.y);
}

void InputManager::ShowMyCursor(const bool& aIsVisible)
{
	ShowCursor(aIsVisible);
}