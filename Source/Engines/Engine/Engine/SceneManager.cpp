#include "SceneManager.h"

#include <Engine/AssetManagement/AssetManager.h>

std::vector<AssetPointer<Scene>> SceneManager::loadedScenes;

void SceneManager::Load(const char* aScene)
{
	loadedScenes.push_back(AssetManager::Get<Scene>(aScene));
}
