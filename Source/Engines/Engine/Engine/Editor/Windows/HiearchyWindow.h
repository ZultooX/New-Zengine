#pragma once

#include "Window.h"

class HiearchyWindow final : public AbstractWindow {
public:
	HiearchyWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;
};