#pragma once
#include "Window.h"


class InputManagerWindow final : public AbstractWindow
{
public:
	InputManagerWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

private:
	int myActiveGamepad = -1;
};

