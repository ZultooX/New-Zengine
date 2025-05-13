#include "InspectorWindow.h"

#include <Zultools/Random.h>
#include <Engine/ComponentSystem/GameObjectManager.h>
#include <ImGui/imgui.h>
#include "HiearchyWindow.h"

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
	ImGui::DragFloat("Near", &aComponent->nearPlane, 0.01f, FLT_MIN, aComponent->farPlane);
	ImGui::DragFloat("Far", &aComponent->farPlane, 0.01f, aComponent->nearPlane, FLT_MAX);

	ImGui::DragFloat("Field of View", &aComponent->fov, 0.2f);
}
