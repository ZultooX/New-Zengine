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
#pragma region Components

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

#pragma endregion


};

template<typename T>
inline void InspectorWindow::DrawComponent(T* aComponent)
{
	using namespace Zengine::ComponentSystem;

	if (aComponent->GetTypeIdx() == typeid(Zengine::ComponentSystem::Transform))
	{
		DrawComponent(dynamic_cast<Zengine::ComponentSystem::Transform*>(aComponent));
		return;
	}
	else if (aComponent->GetTypeIdx() == typeid(MeshRenderer))
	{
		DrawComponent(dynamic_cast<MeshRenderer*>(aComponent));
		return;
	}
	else if (aComponent->GetTypeIdx() == typeid(EditorCamera))
	{
		DrawComponent(dynamic_cast<EditorCamera*>(aComponent));
		return;
	}
	else if (aComponent->GetTypeIdx() == typeid(Camera))
	{
		DrawComponent(dynamic_cast<Camera*>(aComponent));
		return;
	}
	else
	{
		ImGui::Text("Not implemented: "  stringify(T));
		return;
	}
}

template<>
inline void InspectorWindow::DrawComponent(Zengine::ComponentSystem::Transform* aComponent)
{
	bool wasDrawn = aComponent->GetBit(Zengine::ComponentSystem::EditorDrawn);
	DrawComponentHeader("Transform", wasDrawn, 5, ImGuiStyleVar_FrameRounding);
	aComponent->SetBit(Zengine::ComponentSystem::EditorDrawn, wasDrawn);
	if (!wasDrawn) return;

	{ // Position
		Vector3f pos = aComponent->GetPosition();
		ImGui::DragFloat3("Position", &pos.x, 0.01f);
		if (pos != aComponent->GetPosition()) aComponent->SetPosition(pos);
	}

	{ // Rotation
		Vector3f eAngles = aComponent->GetEulerAngles();
		ImGui::DragFloat3("Rotation", &eAngles.x, 0.01f);
		if (eAngles != aComponent->GetEulerAngles()) aComponent->SetEulerAngles(eAngles);
	}

	{ // Scale 
		Vector3f scale = aComponent->GetScale();
		ImGui::DragFloat3("Scale", &scale.x, 0.01f);
		if (scale != aComponent->GetScale()) aComponent->SetScale(scale);
	}
}

template<>
inline void InspectorWindow::DrawComponent(Zengine::ComponentSystem::MeshRenderer* aComponent)
{
	bool wasDrawn = aComponent->GetBit(Zengine::ComponentSystem::EditorDrawn);
	DrawComponentHeader("Meshrenderer", wasDrawn, 5, ImGuiStyleVar_FrameRounding);
	aComponent->SetBit(Zengine::ComponentSystem::EditorDrawn, wasDrawn);
	if (!wasDrawn) return;

	ImGui::Text("This is not final.");

	//ImGui::Text(aComponent->GetMesh()->GetName().c_str());

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

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	//ImGui::DragFloat("Movement Multiplier", &aComponent->myMovementSpeedMultiplier, 0.1f);
}

template<>
inline void InspectorWindow::DrawComponent(Zengine::ComponentSystem::Camera* aComponent)
{
	bool wasDrawn = aComponent->GetBit(Zengine::ComponentSystem::EditorDrawn);
	DrawComponentHeader("Camera", wasDrawn, 5, ImGuiStyleVar_FrameRounding);
	aComponent->SetBit(Zengine::ComponentSystem::EditorDrawn, wasDrawn);
	if (!wasDrawn) return;

	ImGui::DragFloat("Near", &aComponent->nearPlane, 0.01f, FLT_MIN, aComponent->farPlane);
	ImGui::DragFloat("Far", &aComponent->farPlane, 0.01f, aComponent->nearPlane, FLT_MAX);

	ImGui::DragFloat("Field of View", &aComponent->fov, 0.2f);
}
