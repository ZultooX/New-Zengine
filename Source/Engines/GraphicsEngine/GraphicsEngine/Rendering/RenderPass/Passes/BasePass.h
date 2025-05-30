#pragma once

#include <GraphicsEngine/Rendering/RenderPass/RenderPass.h>
#include <GraphicsEngine/GBuffer.h>
#include <GraphicsEngine/IO/DepthBuffer.h>
#include <Engine/AssetManagement/Base/AssetPointer.h>


class PixelShader;
class Material;
class BasePass final
{
public:
	BasePass() = default;

public:
	void Start();
	void Render();

public:
	GBuffer& GetGBuffer() { return myGbuffer; }

private:
	void BindMaterial(const Material* aMaterial);

private:
	GBuffer myGbuffer;
	DepthBuffer myDepthBuffer;
	AssetPointer<PixelShader> myPS;
};