#include "ForwardPass.h"

#include <Engine/AssetManagement/AssetManager.h>

#include <GraphicsEngine/GBuffer.h>

#include <Engine/EngineSettings.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/ComponentManager.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/Utilities/MainSingleton.h>
#include <GraphicsEngine/Drawers/MeshDrawer.h>
#include <GraphicsEngine/Buffers/BufferManager.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/AssetManagement/Assets/Material.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Assets/Texture.h>
#include <Engine/AssetManagement/Assets/Mesh.h>
#include <Engine/AssetManagement/AssetManager.h>

#include <Shaders/Common/ConstantBuffers.h>


void ForwardPass::Start()
{
}

void ForwardPass::Render()
{
	//DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	//ge->SetBackBufferAsTarget();

	//Zengine::Graphics::MeshDrawer& drawer = MainSingleton::GetInstance<Zengine::Graphics::MeshDrawer>();

	//for (const SubMesh& sub : myForwardRenderedObjs)
	//{
	//	if (sub.materialIndex < renderer->GetMaterials().size())
	//	{
	//		AssetPointer<Material> mat = renderer->GetMaterials()[sub.materialIndex];

	//		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	//		mat->Bind();
	//		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateBuffers();

	//		for (const TextureData& textureData : mat->GetTextures())
	//		{
	//			ge->GetContext()->PSSetShaderResources(textureData.bindPoint, 1, textureData.texture.Get()->GetShaderResourceAddress());
	//		}
	//		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateMaterialBuffer(mat.Get()->GetMaterialData());
	//		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().Bind();

	//		drawer.Draw(sub, mat->GetPixelShader().Get(), mat->GetVertexShader().Get());
	//	}
	//}
}

void ForwardPass::AddRenderer(Zengine::ComponentSystem::MeshRenderer* aRenderer)
{
	//myForwardRenderedObjs.push_back(aRenderer);
}
