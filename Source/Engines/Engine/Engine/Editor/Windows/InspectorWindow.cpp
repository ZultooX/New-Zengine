#include "InspectorWindow.h"

#include <Zultools/Random.h>
#include <Engine/ComponentSystem/GameObjectManager.h>
#include <ImGui/imgui.h>
#include "HiearchyWindow.h"

#define COMPONENT(Component) { #Component, [](Zengine::ComponentSystem::GameObject* obj){obj->AddComponent<Component>(); } },

namespace {
	std::unordered_map<const char*, std::function<void(Zengine::ComponentSystem::GameObject*)>> info = {
		COMPONENT(Zengine::ComponentSystem::Transform)
		COMPONENT(Zengine::ComponentSystem::MeshRenderer)
		COMPONENT(Zengine::ComponentSystem::EditorCamera)
		COMPONENT(Zengine::ComponentSystem::Camera)
	};
}

InspectorWindow::InspectorWindow(const int& aId)
{
	myWindowName = "Inspector";
	myID = aId == -1 ? Random::GetValue<int>() : aId;
}

void InspectorWindow::Open()
{
}

void InspectorWindow::Update()
{
	Zengine::ComponentSystem::GameObject* obj = Zengine::ComponentSystem::GameObjectManager::GetGameObject(HiearchyWindow::ActiveGameObject);

	if (HiearchyWindow::ActiveGameObject == -1) return;
	if (!obj) return;

	ImGui::Text(std::to_string(obj->GetID()).c_str());

	for (Zengine::ComponentSystem::Component* comp : Zengine::ComponentSystem::ComponentManager::GetComponents(HiearchyWindow::ActiveGameObject))
	{
		DrawComponent(comp);
	}




	if (ImGui::Button("Add Component"))
	{
		ImGui::OpenPopup("AddComponentPopup");
	}

	if (ImGui::BeginPopup("AddComponentPopup"))
	{
		for (const auto& [name, type] : info)
		{
			if (ImGui::MenuItem(name))
			{
				type(obj);
				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::EndPopup();
	}
}

void InspectorWindow::Close()
{
}

void InspectorWindow::DrawComponentHeader(const char* compName, bool& isDrawn, const float values, ImGuiStyleVar styleFlags)
{
	ImGui::PushStyleVar(styleFlags, values);
	isDrawn = ImGui::CollapsingHeader(compName);
	ImGui::PopStyleVar();
}

void InspectorWindow::DrawSharedCamera(Zengine::ComponentSystem::Camera* aComponent)
{

}
