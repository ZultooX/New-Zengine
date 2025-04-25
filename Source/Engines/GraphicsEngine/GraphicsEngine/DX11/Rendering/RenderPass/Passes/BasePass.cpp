#include "BasePass.h"



#include <Engine/Engine.h>
#include <Engine/EngineSettings.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/ComponentManager.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/Utilities/MainSingleton.h>
#include <GraphicsEngine/DX11/Drawers/MeshDrawer.h>
#include <GraphicsEngine/DX11/Buffers/BufferDatas.h>
#include <GraphicsEngine/DX11/Buffers/BufferManager.h>

#include <GraphicsEngine/Shader/Shaders/PixelShader.h>
#include <Engine/AssetManagement/PixelShaderManager.h>
#include <Engine/AssetManagement/TextureManager.h>

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
		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateObjectBuffer(renderer->gameobject->transform->transformMatrix);
		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateBuffers();
		MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().Bind();

		std::string* textures = renderer->GetTextures();
		for (int i = 0; i < TextureSlot::COUNT; i++)
		{
			if (textures[i].empty()) continue;

			textureManager.Get(textures[i])->SetAsResourceOnSlot(i);
		}

		drawer.Draw(renderer, myPsShader, renderer->GetVertexShader());
	}

	myGbuffer.Unbind();
}
