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

namespace Zengine::Graphics
{
	class VertexShader;
	class PixelShader;

	class MeshDrawer final
	{
	public:
		static void Draw(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer);
		static void Draw(const SubMesh& aMesh, PixelShader* aPixelShader, VertexShader* aVertexShader);

		void BindMaterial(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer, const unsigned& aIdx);

	};
}