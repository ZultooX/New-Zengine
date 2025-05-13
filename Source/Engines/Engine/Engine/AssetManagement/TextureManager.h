#pragma once

#include "AssetManager.h"
#include <GraphicsEngine/DX11/IO/Texture.h>

class TextureManager final : public AbstractAssetManager<Texture>
{
public:
	Texture* Load(const std::string& aTexturePath) override;

	Texture* GetDefaultNormal();

private:
	Texture* LoadDDS(const std::string& aTexturePath);
	Texture* LoadSTB(const std::string& aTexturePath);

private:
	std::string myDefaultNormalPath = ZENGINE_TEXTURES_PATH "Engine/Default_Texture_N.png";
};