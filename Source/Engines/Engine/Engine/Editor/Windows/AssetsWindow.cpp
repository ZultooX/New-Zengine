#include "AssetsWindow.h"
#include <Zultools/Random.h>
#include <ImGui/imgui.h>

#include <filesystem>
#include <Engine/Utilities/MainSingleton.h>
#include <Engine/Files/FileTypes.h>

#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Assets/Texture.h>


AssetsWindow::AssetsWindow(const int& aId)
{
	myWindowName = "Assets";
	myID = aId == -1 ? Random::GetValue<int>() : aId;
}

void AssetsWindow::Open()
{
}

void AssetsWindow::Update()
{
	if (myCurrentFilePath + "/" != ZENGINE_ASSETS_PATH)
	{
		if (ImGui::GetIO().MouseClicked[3])
		{
			myCurrentFilePath = std::filesystem::path(myCurrentFilePath).parent_path().string();
		}
	}

	auto i = std::string(ZENGINE_BIN_PATH).size();

	ImGui::Text(myCurrentFilePath.substr(i).c_str());
	ImGui::Separator();

	int x = 0, y = 0, xIndex = 1, yIndex = 0;

	for (auto& entry : std::filesystem::directory_iterator(myCurrentFilePath))
	{
		if (entry.is_directory())
		{
			Texture* icon = GetDirectoryIcon();

			if (Draw(x, y, xIndex, yIndex, entry.path().filename().stem().string().c_str(), entry.path().string().c_str(), icon))
			{
				myCurrentFilePath = entry.path().string();
			}
		}
		else
		{
			const FileTypes& type = fileExtensionToType[entry.path().extension().string()];

			//Texture* icon = nullptr;

			//switch (type)
			//{
			//case FileTypes::MESH:
			//	 icon = GetMeshIcon();
			//	Draw(x, y, xIndex, yIndex, entry.path().filename().stem().string().c_str(), entry.path().string().c_str(), icon);
			//	break;

			//case FileTypes::TEXTURE:
			//	 icon = GetTexture(entry.path().string().c_str());
			//	Draw(x, y, xIndex, yIndex, entry.path().filename().stem().string().c_str(), entry.path().string().c_str(), icon);
			//	break;

			//case FileTypes::MATERIAL:
			//	 icon = GetMaterialIcon();
			//	Draw(x, y, xIndex, yIndex, entry.path().filename().stem().string().c_str(), entry.path().string().c_str(), icon);
			//	break;

			//default:
			//	ImGui::Text("HEJSAN");
			//	break;
			//}

			
		}

		ImGui::SameLine();

		x += 100;
		++xIndex;
	}
}

void AssetsWindow::Close()
{
}

Texture* AssetsWindow::GetDirectoryIcon()
{
	static AssetPointer<Texture> icon = AssetManager::Get<Texture>(ZENGINE_ENGINE_EDITOR_ICONS_PATH "folder_icon.png");
	return icon.Get();
}

Texture* AssetsWindow::GetMeshIcon()
{
	static AssetPointer<Texture> icon = AssetManager::Get<Texture>(ZENGINE_ENGINE_EDITOR_ICONS_PATH "mesh_icon.png");
	return icon.Get();
}

Texture* AssetsWindow::GetMaterialIcon()
{
	static AssetPointer<Texture> icon = AssetManager::Get<Texture>(ZENGINE_ENGINE_EDITOR_ICONS_PATH "material_icon.png");
	return icon.Get();
}

Texture* AssetsWindow::GetTexture(const char* aPath)
{
	AssetPointer<Texture> texture = AssetManager::Get<Texture>(aPath);
	return texture.Get();
}

bool AssetsWindow::Draw(int& x, const int& y, int& xIndex, int& yIndex, const char* aName, const char* aPath, Texture* texture)
{
	ImVec2 pos = ImVec2(x + 20 * xIndex, y + 60 + (yIndex * 140));

	ImGui::SetCursorPos(pos);
	bool returnValue = ImGui::ImageButton(aName, texture->GetShaderResource(), { 100, 100 });

	ImVec2 textSize = ImGui::CalcTextSize(aName);

	ImVec2 titlePos = ImVec2(pos.x + 50 - (textSize.x / 2), pos.y + 100 + (textSize.y / 2));
	ImGui::SetCursorPos(titlePos);
	ImGui::Text(aName);

	ImVec2 windowSize = ImGui::GetWindowSize();

	if (pos.x + 240 > windowSize.x)
	{
		++yIndex;
		xIndex = 0;
		x = -100;
	}

	if (ImGui::BeginItemTooltip())
	{
		ImGui::Text(aName);
		ImGui::EndTooltip();
	}

	return returnValue;
}
