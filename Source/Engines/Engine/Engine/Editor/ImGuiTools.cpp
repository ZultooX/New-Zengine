#ifdef _DEBUG

#include "ImGuiTools.h"

#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui.h>
#include <Engine/Engine.h>

#include <d3d11.h>

void ImGuiTools::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(gHWND);

	DX11GraphicsEngine& ge = *static_cast<DX11GraphicsEngine*>(Engine::GetGraphicsEngine());
	ImGui_ImplDX11_Init(ge.GetDevice(), ge.GetContext());
}

void ImGuiTools::NewImGuiFrame()
{
	const EngineSettings& settings = Engine::GetSettings();
	ImGui::GetIO().DisplaySize = ImVec2(settings.GetResolution().x, settings.GetResolution().y);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(1, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void ImGuiTools::RenderImGui()
{
	//Editor::GetInstance()->RenderUI();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
}

void ImGuiTools::OnResize()
{
	Cleanup();
	InitImGui();
}

void ImGuiTools::RenderView(ID3D11ShaderResourceView* atexture)
{
	ImGui::Begin("Viewport");

	ImGui::Image(atexture, { 300,300 });

	ImGui::End();
}

void ImGuiTools::Cleanup()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
#endif // _DEBUG