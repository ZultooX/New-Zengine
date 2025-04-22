#pragma once
#include "AssetManager.h"
#include <GraphicsEngine/Shader/Shaders/PixelShader.h>

class PixelShaderManager final : public AbstractAssetManager<Zengine::Graphics::PixelShader>
{
protected:
	Zengine::Graphics::PixelShader* Load(const std::string& aShaderPath) override;
};