#include "BasePass.h"



#include <Engine/Engine.h>
#include <Engine/EngineSettings.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/ComponentManager.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/Utilities/MainSingleton.h>
#include <GraphicsEngine/DX11/Drawers/MeshDrawer.h>
#include <GraphicsEngine/DX11/Buffers/BufferManager.h>

#include <GraphicsEngine/Shader/Shaders/PixelShader.h>
#include <Engine/AssetManagement/PixelShaderManager.h>
#include <Engine/AssetManagement/TextureManager.h>
#include <Engine/AssetManagement/MaterialManager.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>
#include <GraphicsEngine/DX11/Materials/Material.h>

#include <Shaders/Common/ConstantBuffers.h>


void BasePass::Start()
{
	Vector2i size = Engine::GetSettings().GetResolution();
	myGbuffer = GBuffer::Create(size);
	myDepthBuffer.Create(size);
	myPsShader = MainSingleton::GetInstance<PixelShaderManager>().Get(ZENGINE_SHADERS_PATH "PS_GBuffer.cso");
}

void BasePass::Render()
{
	myGbuffer.ClearTextures();
	myDepthBuffer.Clear();

	myGbuffer.SetAsActiveTarget(&myDepthBuffer);

	TextureManager& textureManager = MainSingleton::GetInstance<TextureManager>();
	Zengine::Graphics::MeshDrawer& drawer = MainSingleton::GetInstance<Zengine::Graphics::MeshDrawer>();
	for (CS::MeshRenderer* renderer : Zengine::ComponentSystem::ComponentManager::GetComponents<CS::MeshRenderer>())
	{
		renderer->gameobject->transform->UpdateTransformMatricies();
		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateObjectBuffer(renderer->gameobject->transform->GetTransformMatrix());
		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().Bind();

		for (const SubMesh& sub : renderer->GetMesh()->meshes)
		{
			if (sub.materialIndex < renderer->GetMaterials().size())
			{
				Material* material = MainSingleton::GetInstance<MaterialManager>().Get(renderer->GetMaterials()[sub.materialIndex]);

				BindMaterial(material);


				drawer.Draw(sub, myPsShader, material->GetShader().GetVertexShader());
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
		Texture* texture = MainSingleton::GetInstance<TextureManager>().Get(ZENGINE_ASSETS_PATH + textureData.texturePath);

		ge->GetContext()->PSSetShaderResources(textureData.bindSlot, 1, texture->GetSRVAddress());
	}
}
