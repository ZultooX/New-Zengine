#include "Editor.h"

#include "ImGuiTools.h"
#include <ImGui/imgui.h>
#include <Engine/Engine.h>
#include "Windows/ConsoleWindow.h"

std::unordered_map<unsigned, AbstractWindow*> Editor::IdToWindow;


void Editor::Init()
{
	ImGuiTools::InitImGui();
}

void Editor::Update()
{
	ImGuiTools::NewImGuiFrame();

	UpdateMainMenuBar();

	for (auto it = IdToWindow.begin(); it != IdToWindow.end(); )
	{
		const unsigned& id = it->first;
		AbstractWindow* window = it->second;

		if (window->myWasLastOpen != window->myIsOpen)
		{
			delete window;
			it = IdToWindow.erase(it);
		}
		else
		{
			std::string imguiWindowName = window->GetWindowName() + "##" + std::to_string(id);
			ImGui::Begin(imguiWindowName.c_str(), &window->myIsOpen, 0);
			window->Update();
			ImGui::End();

			++it;
		}
	}
}

void Editor::Render()
{
	ImGuiTools::RenderImGui();
}

void Editor::UpdateMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("Console"))
			{
				ConsoleWindow* window = new ConsoleWindow();
				window->Open();
				IdToWindow[window->GetID()] = window;
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}
