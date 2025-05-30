#include "BasePass.h"



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
#include <GraphicsEngine/Rendering/RenderPass/RenderPassManager.h>

#define PS 1653738650775372633

void BasePass::Start()
{
	Vector2i size = Engine::GetSettings().GetResolution();
	myGbuffer = GBuffer::Create(size);
	myDepthBuffer.Create(size);
	myPS = AssetManager::Get<PixelShader>(ZENGINE_PIXEL_SHADERS_PATH "PS_GBuffer.cso");
}

void BasePass::Render()
{
	myGbuffer.ClearTextures();
	myDepthBuffer.Clear();

	myGbuffer.SetAsActiveTarget(&myDepthBuffer);

	Zengine::Graphics::MeshDrawer& drawer = MainSingleton::GetInstance<Zengine::Graphics::MeshDrawer>();
	for (CS::MeshRenderer* renderer : Zengine::ComponentSystem::ComponentManager::GetComponents<CS::MeshRenderer>())
	{
		renderer->gameobject->transform->UpdateTransformMatricies();
		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateObjectBuffer(renderer->gameobject->transform->GetTransformMatrix());
		

		for (const SubMesh& sub : renderer->GetMesh()->GetSubmeshes())
		{
			if (sub.materialIndex < renderer->GetMaterials().size())
			{
				AssetPointer<Material> mat = renderer->GetMaterials()[sub.materialIndex];

				//if (mat->GetPixelShader()->GetID() != PS)
				//{
				//	MainSingleton::GetInstance<RenderPassManager>().GetForwardPass().AddRenderer()
				//}

				BindMaterial(mat.Get());
				MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateMaterialBuffer(mat.Get()->GetMaterialData());
				MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().Bind();

				drawer.Draw(sub, myPS.Get(), mat->GetVertexShader().Get());
			}
		}
	}

	myGbuffer.Unbind();
}

void BasePass::BindMaterial(const Material* aMaterial)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	aMaterial->Bind();
	MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateBuffers();

	for (const TextureData& textureData : aMaterial->GetTextures())
	{
		ge->GetContext()->PSSetShaderResources(textureData.bindPoint, 1, textureData.texture.Get()->GetShaderResourceAddress());
	}
}
