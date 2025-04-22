#pragma once


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
		static void Draw(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer, PixelShader* aPixelShader, VertexShader* aVertexShader);

	};
}