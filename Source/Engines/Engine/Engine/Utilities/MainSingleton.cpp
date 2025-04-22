#include "MainSingleton.h"

#include <GraphicsEngine/GraphicsEngine.h>

#include <Zultools/InputManager.h>

#include <Engine/AssetManagement/MeshManager.h>
#include <Engine/AssetManagement/PixelShaderManager.h>
#include <Engine/AssetManagement/VertexShaderManager.h>
#include <Engine/AssetManagement/TextureManager.h>
#include <GraphicsEngine/DX11/Drawers/MeshDrawer.h>
#include <GraphicsEngine/DX11/Buffers/BufferManager.h>
#include <Zultools/Timer.h>

#include <GraphicsEngine/DX11/Rendering/RenderPass/RenderPassManager.h>

std::unordered_map<std::string, void*> MainSingleton::mySingletons;
bool MainSingleton::myIsInitialized = false;


void MainSingleton::Setup()
{
	myIsInitialized = true;

	RegisterInstance<RenderPassManager>();

	RegisterInstance<MeshManager>();
	GetInstance<MeshManager>().Init();

	RegisterInstance<PixelShaderManager>();
	RegisterInstance<VertexShaderManager>();
	RegisterInstance<TextureManager>();

	RegisterInstance<Zengine::Buffers::BufferManager>();

	RegisterInstance<Zengine::Graphics::MeshDrawer>();

	RegisterInstance<CommonUtilities::Timer>();
}

const bool& MainSingleton::IsSetup() { return myIsInitialized; }