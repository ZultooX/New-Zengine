#pragma once
#include "AssetManager.h"
#include <GraphicsEngine/DX11/Materials/Material.h>

class MaterialManager final : public AbstractAssetManager<Material>
{
protected:
	Material* Load(const std::string& aMaterialPath) override;
};