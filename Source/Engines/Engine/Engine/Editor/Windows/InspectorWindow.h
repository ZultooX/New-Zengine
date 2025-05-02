#pragma once

#include "Window.h"
#include <ImGui/imgui.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/EditorCamera.h>

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
	template<typename T>
	void DrawComponent(T* aComponent);

	template<>
	void DrawComponent(Zengine::ComponentSystem::Transform* aComponent);

	template<>
	void DrawComponent(Zengine::ComponentSystem::MeshRenderer* aComponent);

	template<>
	void DrawComponent(Zengine::ComponentSystem::EditorCamera* aComponent);

};

template<typename T>
inline void InspectorWindow::DrawComponent(T* aComponent)
{
	if (Zengine::ComponentSystem::Transform* comp = dynamic_cast<Zengine::ComponentSystem::Transform*>(aComponent))
		DrawComponent(comp);

	else if (Zengine::ComponentSystem::MeshRenderer* comp = dynamic_cast<Zengine::ComponentSystem::MeshRenderer*>(aComponent))
		DrawComponent(comp);

	else if (Zengine::ComponentSystem::EditorCamera* comp = dynamic_cast<Zengine::ComponentSystem::EditorCamera*>(aComponent))
		DrawComponent(comp);
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

	ImGui::Text("THIS IS A MESH RENDERER");
}

template<>
inline void InspectorWindow::DrawComponent(Zengine::ComponentSystem::EditorCamera* aComponent)
{
	bool wasDrawn = aComponent->GetBit(Zengine::ComponentSystem::EditorDrawn);
	DrawComponentHeader("Editor Camera", wasDrawn, 5, ImGuiStyleVar_FrameRounding);
	aComponent->SetBit(Zengine::ComponentSystem::EditorDrawn, wasDrawn);
	if (!wasDrawn) return;

	ImGui::Text("THIS IS A EDITOR CAMERA");
}
