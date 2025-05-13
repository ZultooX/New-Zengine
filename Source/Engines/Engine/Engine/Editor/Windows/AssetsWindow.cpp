#include "AssetsWindow.h"
#include <Zultools/Random.h>
#include <ImGui/imgui.h>

#include <filesystem>




// Display every file in the assets folder.





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
	auto i = std::string(ZENGINE_ASSETS_PATH).size();

	ImGui::Text(myCurrentFilePath.substr(i).c_str());
	ImGui::Separator();

	for (auto& entry : std::filesystem::directory_iterator(myCurrentFilePath))
	{
		if (entry.is_directory())
		{
			if (Directy(entry.path().filename().stem().string().c_str(), entry.path().string().c_str()))
			{
				myCurrentFilePath = entry.path().string();
			}
		}
		else ImGui::Text("HEJSAN");

		ImGui::SameLine();
	}
}

void AssetsWindow::Close()
{
}
bool AssetsWindow::Directy(const char* aName, const char* aPath)
{
	bool returnValue = ImGui::ImageButton(aName, nullptr, { 100, 100 });

	if (ImGui::BeginItemTooltip())
	{
		ImGui::Text(aName);
		ImGui::EndTooltip();
	}

	return returnValue;
}
