#pragma once

#include "Window.h"


class AssetsWindow final : public AbstractWindow {

public:
	AssetsWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

private:

	bool Directy(const char* aName, const char* aPath);

	std::string myCurrentFilePath = ZENGINE_ASSETS_PATH;
};
