#pragma once

#include "Window.h"

struct ID3D11ShaderResourceView;
struct ImVec2;
class RenderingDebuggerWindow final : public AbstractWindow {

public:
	RenderingDebuggerWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

private:
	void DrawImage(const char* aTitle, const ImVec2& aSize, const ImVec2& aOffset, const ImVec2& padding, ID3D11ShaderResourceView* aImage);
	void DrawSquare(const ImVec2& aSize, const ImVec2& aOffset, const ImVec2& padding);
};