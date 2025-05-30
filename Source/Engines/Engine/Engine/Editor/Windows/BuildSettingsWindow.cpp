#include "BuildSettingsWindow.h"

#include <Zultools/Random.h>
#include <ImGui/imgui.h>

#include <Engine/AssetManagement/Exporters/MaterialExporter.h>
#include <Engine/AssetManagement/Exporters/VertexShaderExporter.h>
#include <Engine/AssetManagement/Exporters/PixelShaderExporter.h>
#include <Engine/AssetManagement/Exporters/MeshExporter.h>
#include <Engine/AssetManagement/Exporters/TextureExporter.h>
#include <Engine/AssetManagement/Exporters/SceneExporter.h>
#include <Engine/AssetManagement/Importers/MaterialImporter.h>
#include <Engine/AssetManagement/Importers/MeshImporter.h>
#include <Engine/AssetManagement/Importers/SceneImporter.h>
#include <Engine/AssetManagement/Assets/Material.h>
#include <Engine/AssetManagement/Assets/Mesh.h>
#include <Engine/SceneManager.h>

BuildSettingsWindow::BuildSettingsWindow(const int& aId)
{
	myWindowName = "Build Settings";
	myID = aId == -1 ? Random::GetValue<int>() : aId;
}

void BuildSettingsWindow::Open()
{
}

void BuildSettingsWindow::Update()
{
	if (ImGui::Button("Save Scene")) SceneExporter::SaveScene(ZENGINE_ASSETS_PATH "scene.scene");
	if (ImGui::Button("Load Scene")) SceneManager::Load(ZENGINE_ASSETS_PATH "scene.scene");

	ImGui::Spacing();

	if (ImGui::Button("Export Assets")) ExportAssets();
	if (ImGui::Button("Load Material"))
	{
		Material mat;
		MaterialImporter::Load(95852268924481528, mat);

		Mesh mesh;
		MeshImporter::Load(5179236805684878531, mesh);

		mat.GetAoStrength();
	}
}

void BuildSettingsWindow::Close()
{
}

void BuildSettingsWindow::ExportAssets()
{
	MaterialExporter::ExportAllToBinaryFile(ZENGINE_ASSETS_PATH "materials.bundle");
	MeshExporter::ExportAllToBinaryFile(ZENGINE_ASSETS_PATH "meshes.bundle");
	VertexShaderExporter::ExportAllToBinaryFile(ZENGINE_ASSETS_PATH "pixelshaders.bundle");
	PixelShaderExporter::ExportAllToBinaryFile(ZENGINE_ASSETS_PATH "vertexshaders.bundle");
	TextureExporter::ExportAllToBinaryFile(ZENGINE_ASSETS_PATH "textures.bundle");
}
