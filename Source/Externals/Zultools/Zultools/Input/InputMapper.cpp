#include "InputMapper.h"

#include "Input.h"


void InputMapper::Update()
{
	for (const auto& [id, action] : myMappedActions)
	{
		int value = 0;
		switch (action.Type)
		{
		case ActionType::Hold: value = Input::GetKey(action.Key); break;
		case ActionType::Pressed: value = Input::GetKeyDown(action.Key); break;
		case ActionType::Released: value = Input::GetKeyUp(action.Key); break;
		}

		if (value > 0) action.Action();
	}

	for (const auto& [id, axis] : myMappedAxises)
	{
		const int value = Input::GetKey(axis.PositiveKey) - Input::GetKey(axis.NegativeKey);
		if (value != 0)
		{
			axis.Action(value);
		}
	}
}

void InputMapper::Map(const std::string& anIdentification, const InputAxis& anAxis)
{
	myMappedAxises[anIdentification] = anAxis;
}

void InputMapper::Map(const std::string& anIdentification, const InputAction& anAction)
{
	myMappedActions[anIdentification] = anAction;
}

void InputMapper::Unmap(const std::string& anIdentification)
{
	for (const auto& [id, action] : myMappedActions)
	{
		if (id == anIdentification)
		{
			myMappedActions.erase(id);
			return;
		}
	}

	for (const auto& [id, axis] : myMappedAxises)
	{
		if (id == anIdentification)
		{
			myMappedAxises.erase(id);
			return;
		}
	}
}
