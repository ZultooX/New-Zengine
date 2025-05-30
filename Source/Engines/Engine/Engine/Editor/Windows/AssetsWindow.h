#pragma once

#include "Window.h"

class Texture;
class AssetsWindow final : public AbstractWindow {

public:
	AssetsWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

private:
	Texture* GetDirectoryIcon();
	Texture* GetMeshIcon();
	Texture* GetMaterialIcon();
	Texture* GetTexture(const char* aPath);

	bool Draw(int& x, const int& y, int& xIndex, int& yIndex, const char* aName, const char* aPath, Texture* texture);

	std::string myCurrentFilePath = ZENGINE_ASSETS_PATH;
};
