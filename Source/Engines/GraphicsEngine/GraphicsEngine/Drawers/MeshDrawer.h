#pragma once

#include <GraphicsEngine/GraphicsStructs.h>

namespace Zengine
{
	namespace ComponentSystem
	{
		class MeshRenderer;
	}

	namespace Graphics
	{

	}
}

#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Assets/VertexShader.h>

namespace Zengine::Graphics
{
	class MeshDrawer final
	{
	public:
		static void Draw(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer);
		static void Draw(const SubMesh& aMesh, PixelShader* aPixelShader, VertexShader* aVertexShader);

		void BindMaterial(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer, const unsigned& aIdx);

	};
}