#pragma once
#include <Engine/AssetManagement/Assets/Scene.h>

class SceneManager
{
public:
	static void Load(const char* aScene);


	static std::vector<AssetPointer<Scene>> loadedScenes;
};

