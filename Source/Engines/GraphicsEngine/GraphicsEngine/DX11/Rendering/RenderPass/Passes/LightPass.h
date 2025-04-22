#pragma once

#include <GraphicsEngine/DX11/Rendering/RenderPass/RenderPass.h>

#include <GraphicsEngine/DX11/Rendering/FullscreenSprite.h>
#include <GraphicsEngine/Shader/Shaders/PixelShader.h>

class GBuffer;

class LightPass final 
{
public:
	void Start();
	void Render(GBuffer& aGbuffer);

private:
	Zengine::Graphics::FullscreenSprite myFullscreenEffect;
	Zengine::Graphics::PixelShader* myDeferedPBR_PS;
};