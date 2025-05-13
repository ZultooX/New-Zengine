#pragma once

#include "Window.h"
#include <ImGui/imgui.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/EditorCamera.h>

#define stringify(v) #v

class InspectorWindow final : public AbstractWindow {
public:
	InspectorWindow(const int& aId = -1);

	void Open() override;
	void Update() override;
	void Close() override;

	int ActiveGameObject;
	int ActiveIdx;

private:
	void DrawComponentHeader(const char* compName, bool& isDrawn, const float values = 0, ImGuiStyleVar styleFlags = ImGuiStyleVar_FrameRounding);

private:
	void DrawSharedCamera(Zengine::ComponentSystem::Camera* aComponnent);

private:
	template<typename T>
	void DrawComponent(T* aComponent);

	template<>
	void DrawComponent(Zengine::ComponentSystem::Transform* aComponent);

	template<>
	void DrawComponent(Zengine::ComponentSystem::MeshRenderer* aComponent);

	template<>
	void DrawComponent(Zengine::ComponentSystem::EditorCamera* aComponent);

	template<>
	void DrawComponent(Zengine::ComponentSystem::Camera* aComponent);
};

template<typename T>
inline void InspectorWindow::DrawComponent(T* aComponent)
{
	if (Zengine::ComponentSystem::Transform* comp = dynamic_cast<Zengine::ComponentSystem::Transform*>(aComponent))
	{
		DrawComponent(comp);
		return;
	}

	else if (Zengine::ComponentSystem::MeshRenderer* comp = dynamic_cast<Zengine::ComponentSystem::MeshRenderer*>(aComponent))
	{
		DrawComponent(comp);
		return;
	}

	else if (Zengine::ComponentSystem::EditorCamera* comp = dynamic_cast<Zengine::ComponentSystem::EditorCamera*>(aComponent))
	{
		DrawComponent(comp);
		return;
	}

	bool wasDrawn = false;
	DrawComponentHeader(stringify(T), wasDrawn, 5, ImGuiStyleVar_FrameRounding);
}

template<>
inline void InspectorWindow::DrawComponent(Zengine::ComponentSystem::Transform* aComponent)
{
	bool wasDrawn = aComponent->GetBit(Zengine::ComponentSystem::EditorDrawn);
	DrawComponentHeader("Transform", wasDrawn, 5, ImGuiStyleVar_FrameRounding);
	aComponent->SetBit(Zengine::ComponentSystem::EditorDrawn, wasDrawn);
	if (!wasDrawn) return;

	Vector3f pos = aComponent->GetPosition();
	Vector3f scale = aComponent->GetScale();
	Vector3f euler = aComponent->GetEulerAngles();

	ImGui::DragFloat3("Position", &pos.x, 0.01f);
	ImGui::DragFloat3("Rotation", &euler.x, 0.01f);
	ImGui::DragFloat3("Scale   ", &scale.x, 0.01f);

	aComponent->SetPosition(pos);
	aComponent->SetScale(scale);
	aComponent->SetEulerAngles(euler);
}

template<>
inline void InspectorWindow::DrawComponent(Zengine::ComponentSystem::MeshRenderer* aComponent)
{
	bool wasDrawn = aComponent->GetBit(Zengine::ComponentSystem::EditorDrawn);
	DrawComponentHeader("Meshrenderer", wasDrawn, 5, ImGuiStyleVar_FrameRounding);
	aComponent->SetBit(Zengine::ComponentSystem::EditorDrawn, wasDrawn);
	if (!wasDrawn) return;

	ImGui::Text("This is not final.");

	ImGui::Text(aComponent->GetMesh()->GetName().c_str());

	ImGui::Text("THIS IS A MESH RENDERER");
}

template<>
inline void InspectorWindow::DrawComponent(Zengine::ComponentSystem::EditorCamera* aComponent)
{
	bool wasDrawn = aComponent->GetBit(Zengine::ComponentSystem::EditorDrawn);
	DrawComponentHeader("Editor Camera", wasDrawn, 5, ImGuiStyleVar_FrameRounding);
	aComponent->SetBit(Zengine::ComponentSystem::EditorDrawn, wasDrawn);
	if (!wasDrawn) return;

	Zengine::ComponentSystem::Camera* cam = dynamic_cast<Zengine::ComponentSystem::Camera*>(aComponent);
	DrawSharedCamera(cam);

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	//ImGui::DragFloat("Movement Multiplier", &aComponent->myMovementSpeedMultiplier, 0.1f);
}

template<>
inline void InspectorWindow::DrawComponent(Zengine::ComponentSystem::Camera* aComponent)
{
	bool wasDrawn = aComponent->GetBit(Zengine::ComponentSystem::EditorDrawn);
	DrawComponentHeader("Editor Camera", wasDrawn, 5, ImGuiStyleVar_FrameRounding);
	aComponent->SetBit(Zengine::ComponentSystem::EditorDrawn, wasDrawn);
	if (!wasDrawn) return;

	DrawSharedCamera(aComponent);
}
