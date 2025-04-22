#pragma once
#include "AssetManager.h"
#include <GraphicsEngine/Shader/Shaders/VertexShader.h>

class VertexShaderManager final : public AbstractAssetManager<Zengine::Graphics::VertexShader>
{
protected:
	Zengine::Graphics::VertexShader* Load(const std::string& aShaderPath) override;
};