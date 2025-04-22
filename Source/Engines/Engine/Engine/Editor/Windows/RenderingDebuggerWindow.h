#pragma once

#include "Window.h"


class RenderingDebuggerWindow final : public AbstractWindow {

public:
	RenderingDebuggerWindow();

	void Open() override;
	void Update() override;
	void Close() override;
};