#include "HiearchyWindow.h"

#include <Zultools/Random.h>
#include <Engine/ComponentSystem/GameObjectManager.h>
#include <ImGui/imgui.h>

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
	auto list = Zengine::ComponentSystem::GameObjectManager::GetGameObjects();
	for (auto& [id, obj] : list)
	{
		ImGui::Text(std::to_string(id).c_str());
	}
}

void HiearchyWindow::Close()
{
}
