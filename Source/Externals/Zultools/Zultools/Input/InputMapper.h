#pragma once

#include "Keycode.h"
#include <functional>
#include <vector>
#include <string>

enum class ActionType
{
	Hold, Released, Pressed
};

struct InputAction 
{
	Keycode Key;
	ActionType Type;
	std::function<void()> Action;
};

struct InputAxis
{
	Keycode NegativeKey;
	Keycode PositiveKey;

	std::function<void(int)> Action;
};

class InputMapper
{
public:
	void Update();

public:
	void Map(const std::string& anIdentification, const InputAxis& anAxis);
	void Map(const std::string& anIdentification, const InputAction& anAction);

	void Unmap(const std::string& anIdentification);

private:
	std::unordered_map<std::string, InputAxis> myMappedAxises;
	std::unordered_map<std::string, InputAction> myMappedActions;
};