#pragma once

#include "Window.h"

class ConsoleWindow final : public AbstractWindow {

public:
	ConsoleWindow();

	void Open() override;
	void Update() override;
	void Close() override;
};