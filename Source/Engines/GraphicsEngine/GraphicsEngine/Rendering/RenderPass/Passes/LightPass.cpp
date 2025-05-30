#include "LightPass.h"

#include <Engine/AssetManagement/AssetManager.h>

#include <GraphicsEngine/GBuffer.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

void LightPass::Start()
{
	myFullscreenEffect = Zengine::Graphics::FullscreenSprite(ZENGINE_PIXEL_SHADERS_PATH"PS_DeferedPBR.cso");
}

void LightPass::Render(GBuffer& aGbuffer)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	aGbuffer.SetAllAsResources(3);

	ge->SetBackBufferAsTarget();
	myFullscreenEffect.Render();
}
