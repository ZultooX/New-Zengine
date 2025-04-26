#pragma once

#include "Window.h"


class RenderingDebuggerWindow final : public AbstractWindow {

public:
	RenderingDebuggerWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;
};