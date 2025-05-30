#include "AssetManager.h"

#include <Engine/AssetManagement/Assets/Mesh.h>
#include <Engine/AssetManagement/Assets/Texture.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Assets/VertexShader.h>
#include <Engine/AssetManagement/Assets/Material.h>
#include <Engine/AssetManagement/Assets/Scene.h>

std::unordered_map<std::type_index, BaseList*> AssetManager::AssetLists =
{
	{ typeid(Texture), new AssetList<Texture> },
	{ typeid(Mesh), new AssetList<Mesh> },
	{ typeid(PixelShader), new AssetList<PixelShader> },
	{ typeid(VertexShader), new AssetList<VertexShader> },
	{ typeid(Material), new AssetList<Material> },
	{ typeid(Scene), new AssetList<Scene> },
};