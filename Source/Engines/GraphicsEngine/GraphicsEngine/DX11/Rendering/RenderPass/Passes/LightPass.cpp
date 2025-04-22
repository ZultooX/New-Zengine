#include "LightPass.h"

#include <GraphicsEngine/Shader/Shaders/PixelShader.h>
#include <Engine/AssetManagement/PixelShaderManager.h>

#include <GraphicsEngine/DX11/GBuffer.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

void LightPass::Start()
{
	myFullscreenEffect.SetPixelShader(ZENGINE_SHADERS_PATH"PS_DeferedPBR.cso");
}

void LightPass::Render(GBuffer& aGbuffer)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	aGbuffer.SetAllAsResources(3);

	ge->SetBackBufferAsTarget();
	myFullscreenEffect.Render();
}
