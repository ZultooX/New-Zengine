#pragma once

#include "Window.h"

namespace Zengine::ComponentSystem
{
	class GameObject;
}

class HiearchyWindow final : public AbstractWindow {
public:
	HiearchyWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

	static int ActiveGameObject;
	static int ActiveIdx;
};