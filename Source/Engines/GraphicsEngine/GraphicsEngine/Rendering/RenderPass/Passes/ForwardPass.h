#pragma once

#include <GraphicsEngine/Rendering/RenderPass/RenderPass.h>

#include <GraphicsEngine/Rendering/FullscreenSprite.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Base/AssetPointer.h>
#include <GraphicsEngine/GraphicsStructs.h>

namespace Zengine::ComponentSystem
{
	class MeshRenderer;
}
class GBuffer;

class ForwardPass final 
{
public:
	ForwardPass() = default;

public:
	void Start();
	void Render();

public:
	void AddRenderer(Zengine::ComponentSystem::MeshRenderer* aRenderer);


private:
	std::vector<SubMesh> myForwardRenderedObjs;
};