#pragma once

#include <Engine/AssetManagement/Base/Asset.h>		
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Importers/SceneImporter.h>
#include <Engine/AssetManagement/Exporters/SceneExporter.h>

class Scene : public Asset
{
	BASE_ASSET(Scene, SceneImporter, SceneExporter)

public:

private:

};