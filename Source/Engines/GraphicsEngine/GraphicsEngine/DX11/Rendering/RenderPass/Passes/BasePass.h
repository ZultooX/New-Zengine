#pragma once

#include <GraphicsEngine/DX11/Rendering/RenderPass/RenderPass.h>
#include <GraphicsEngine/DX11/GBuffer.h>
#include <GraphicsEngine/DX11/IO/DepthBuffer.h>


namespace Zengine::Graphics
{
	class PixelShader;
}

class BasePass final
{
public:
	void Start();
	void Render();

public:
	GBuffer& GetGBuffer() { return myGbuffer; }

private:
	GBuffer myGbuffer;
	DepthBuffer myDepthBuffer;
	Zengine::Graphics::PixelShader* myPsShader;
};