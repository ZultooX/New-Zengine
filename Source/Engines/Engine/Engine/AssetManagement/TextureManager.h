#pragma once

#include "AssetManager.h"
#include <GraphicsEngine/DX11/IO/Texture.h>

class TextureManager final : public AbstractAssetManager<Texture>
{
public:
	Texture* Load(const std::string& aTexturePath) override;

private:
	Texture* LoadDDS(const std::string& aTexturePath);
	Texture* LoadSTB(const std::string& aTexturePath);
};