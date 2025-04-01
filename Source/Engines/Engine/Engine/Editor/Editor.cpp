#include "Editor.h"

#include "ImGuiTools.h"
#include <ImGui/imgui.h>
#include <Engine/Engine.h>

void Editor::Init()
{
	ImGuiTools::InitImGui();
}

void Editor::Update()
{
	ImGuiTools::NewImGuiFrame();
}

void Editor::Render()
{
	ImGuiTools::RenderImGui();
}
