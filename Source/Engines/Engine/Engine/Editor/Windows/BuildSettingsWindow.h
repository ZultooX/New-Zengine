#pragma once

#include "Window.h"

class Texture;
class BuildSettingsWindow final : public AbstractWindow {

public:
	BuildSettingsWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

private:
	void ExportAssets();
};
