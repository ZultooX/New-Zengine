#pragma once

#include <fstream>


class Scene;
class SceneImporter
{
public:
	static void Load(const size_t& aID, Scene& aOutAsset);
	static void Load(const char* aPath, Scene& aOutAsset);
	static void Unload(Scene& aOutAsset);
};