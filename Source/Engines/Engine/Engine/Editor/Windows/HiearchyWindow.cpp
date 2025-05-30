#include "HiearchyWindow.h"

#include <Zultools/Random.h>
#include <Engine/ComponentSystem/GameObjectManager.h>
#include <Engine/ComponentSystem/GameObject.h>
#include <ImGui/imgui.h>

int HiearchyWindow::ActiveGameObject = -1;
int HiearchyWindow::ActiveIdx = -1;

HiearchyWindow::HiearchyWindow(const int& aId)
{
	myWindowName = "Hiearchy";
	myID = aId == -1 ? Random::GetValue<int>() : aId;
}

void HiearchyWindow::Open()
{
}

void HiearchyWindow::Update()
{
	constexpr ImVec4 normalColor = ImVec4(0.137f, 0.27f, 0.427f, 1.f);
	constexpr ImVec4 highlightedColor = ImVec4(0.194f, 0.33f, 0.727f, 1.f);

	auto list = Zengine::ComponentSystem::GameObjectManager::GetGameObjects();
	int i = 0;
	for (auto& [id, obj] : list)
	{
		if (i == ActiveIdx)
		{
			ImGui::GetStyle().Colors[ImGuiCol_Button] = highlightedColor;
		}

		if (ImGui::Button((obj->GetName() + "##" + std::to_string(obj->GetID())).c_str()))
		{
			ActiveGameObject = id;
			ActiveIdx = i;
		}

		if (i == ActiveIdx)
		{
			ImGui::GetStyle().Colors[ImGuiCol_Button] = normalColor;
		}

		++i;
	}

	if (ImGui::IsWindowHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
	{
		ImGui::OpenPopup("RightClickMenu");
	}

	if (ImGui::BeginPopup("RightClickMenu"))
	{
		if (ImGui::BeginMenu("Create"))
		{
			if (ImGui::Button("GameObject"))
			{
				Zengine::ComponentSystem::GameObject* obj = Zengine::ComponentSystem::GameObject::Create();
				ActiveGameObject = obj->GetID();
			}

			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}
}

void HiearchyWindow::Close()
{
}
