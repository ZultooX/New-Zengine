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

#include <Engine/Objects/Base/AssetPointer.hpp>
#include <Engine/Objects/AssetManagement/Assets/Mesh.h>
#include <Engine/Objects/AssetManagement/Assets/Shaders/PixelShader.h>
#include <Engine/Objects/AssetManagement/Assets/Shaders/VertexShader.h>

namespace Zengine::Graphics
{
	class MeshDrawer final
	{
	public:
		static void Draw(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer);
		static void Draw(AssetPointer<Mesh>& aMesh, PixelShader* aPixelShader, VertexShader* aVertexShader);

		void BindMaterial(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer, const unsigned& aIdx);

	};
}