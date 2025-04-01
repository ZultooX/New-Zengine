#pragma once

#define WIN32_LEAN_AND_MEAN  // Exclude rarely used APIs
#define NOSOCKET   
#include <Windows.h>
#include <Zultools/Math/Vector2.hpp>
#include <Zultools/Math/Vector3.hpp>
#include <Zultools/Math/Vector4.hpp>
#include <GraphicsEngine/GraphicsEngine.h>
#include <ImGui/imgui.h>

#ifdef _DEBUG

struct ID3D11ShaderResourceView;

extern HWND gHWND;

namespace ImGuiTools
{
	void InitImGui();
	void NewImGuiFrame();
	void RenderImGui();
	void RenderView(ID3D11ShaderResourceView* atexture);
	void Cleanup();
}
#endif // _DEBUG