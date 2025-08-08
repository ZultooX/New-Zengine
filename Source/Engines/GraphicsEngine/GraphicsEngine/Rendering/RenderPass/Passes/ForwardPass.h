#pragma once

#include <GraphicsEngine/Rendering/RenderPass/RenderPass.h>

#include <GraphicsEngine/Rendering/FullscreenSprite.h>
#include <Engine/Objects/AssetManagement/Assets/Shaders/PixelShader.h>
#include <Engine/Objects/Base/AssetPointer.hpp>
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