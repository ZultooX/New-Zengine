#include "Editor.h"
#ifdef _DEBUG

#include "ImGuiTools.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>
#include <Engine/Engine.h>

#include "Windows/ConsoleWindow.h"
#include "Windows/RenderingDebuggerWindow.h"
#include "Windows/HiearchyWindow.h"
#include "Windows/InspectorWindow.h"
#include <fstream>

std::unordered_map<unsigned, AbstractWindow*> Editor::IdToWindow;


void Editor::Init()
{
	ImGuiTools::InitImGui();

	std::ifstream file(ZENGINE_SETTINGS_PATH"Editor.ini");

	std::string nameLine;
	std::string idLine;
	while (std::getline(file, nameLine))
	{
		std::getline(file, idLine);

		int id = std::stoi(idLine);
		OpenWindow(nameLine, id);
	}
}

void Editor::PreUpdate()
{
	ImGuiTools::NewImGuiFrame();
}

void Editor::Update()
{

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

void Editor::OnResize()
{
	ImGuiTools::OnResize();
}

void Editor::UpdateMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Windows"))
		{
			if (ImGui::MenuItem("Console")) OpenWindow("Console", -1);
			if (ImGui::MenuItem("Rendering Debugger")) OpenWindow("Rendering Debugger", -1);
			if (ImGui::MenuItem("Hiearchy")) OpenWindow("Hiearchy", -1);
			if (ImGui::MenuItem("Inspector")) OpenWindow("Inspector", -1);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void Editor::OpenWindow(const std::string& aName, const int& aId)
{
	AbstractWindow* window = nullptr;

	if (aName == "Console")
	{
		window = new ConsoleWindow(aId);
	}
	else if (aName == "Rendering Debugger")
	{
		window = new RenderingDebuggerWindow(aId);
	}
	else if (aName == "Hiearchy")
	{
		window = new HiearchyWindow(aId);
	}
	else if (aName == "Inspector")
	{
		window = new InspectorWindow(aId);
	}

	if (window == nullptr) return;

	window->Open();
	IdToWindow[window->GetID()] = window;
}

void Editor::Save()
{
	std::ofstream file(ZENGINE_SETTINGS_PATH"Editor.ini");

	for (auto& [id, window] : IdToWindow)
	{
		file << window->GetWindowName() << "\n"
			<< std::to_string(window->GetID()) << "\n";
	}

	file.close();
}

#endif
