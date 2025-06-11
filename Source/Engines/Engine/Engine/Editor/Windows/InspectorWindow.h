#pragma once

#include "Window.h"
#include <ImGui/imgui.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/EditorCamera.h>
#include <Engine/AssetManagement/Importers/MeshImporter.h>

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

	{





		int selectedIdx = 0;
		const std::vector<BinaryExporter::MeshIndex>& importedMeshes = MeshImporter::GetImportedAssets();

		size_t currentMeshID = aComponent->GetMesh() ? aComponent->GetMesh()->GetID() : 0;

		std::vector<std::string> stringData = { "No Mesh" };
		for (const auto& mesh : importedMeshes)
		{
			stringData.push_back(mesh.name);
		}

		std::vector<const char*> comboItems;
		for (const auto& str : stringData)
		{
			comboItems.push_back(str.c_str());
		}

		// Determine selected index
		if (currentMeshID != 0)
		{
			for (size_t i = 0; i < importedMeshes.size(); ++i)
			{
				if (importedMeshes[i].id == currentMeshID)
				{
					selectedIdx = static_cast<int>(i + 1); // +1 because "No Mesh" is at index 0
					break;
				}
			}
		}

		if (ImGui::Combo("Mesh##9q0j0j0j0", &selectedIdx, comboItems.data(), static_cast<int>(comboItems.size())))
		{
			if (selectedIdx > 0)
				aComponent->SetMesh(importedMeshes[selectedIdx - 1].id);
		}
	}

	{
		int selectedIdx = 0;
		const auto& importedMaterials = MaterialImporter::GetImportedAssets();

		size_t currentMatID = aComponent->GetMaterial() ? aComponent->GetMaterial()->GetID() : 0;

		std::vector<std::string> stringData = { "No Material" };
		for (const auto& mat : importedMaterials)
		{
			stringData.push_back(std::to_string(mat.id));
		}

		std::vector<const char*> comboItems;
		for (const auto& str : stringData)
		{
			comboItems.push_back(str.c_str());
		}

		if (currentMatID != 0)
		{
			for (size_t i = 0; i < importedMaterials.size(); ++i)
			{
				if (importedMaterials[i].id == currentMatID)
				{
					selectedIdx = static_cast<int>(i + 1);
					break;
				}
			}
		}

		if (ImGui::Combo("Material##eja09fj0989y978yt", &selectedIdx, comboItems.data(), static_cast<int>(comboItems.size())))
		{
			if (selectedIdx > 0)
				aComponent->SetMaterial(importedMaterials[selectedIdx - 1].id);
		}
	}
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
