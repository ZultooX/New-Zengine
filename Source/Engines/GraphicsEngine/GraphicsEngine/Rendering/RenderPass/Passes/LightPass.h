#pragma once

#include <GraphicsEngine/Rendering/RenderPass/RenderPass.h>

#include <GraphicsEngine/Rendering/FullscreenSprite.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Base/AssetPointer.h>

class GBuffer;

class LightPass final 
{
public:
	LightPass() = default;

public:
	void Start();
	void Render(GBuffer& aGbuffer);

private:
	Zengine::Graphics::FullscreenSprite myFullscreenEffect;
	AssetPointer<PixelShader> myDeferedPBR_PS;
};