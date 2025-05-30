#include "MainSingleton.h"

#include <GraphicsEngine/GraphicsEngine.h>

#include <Zultools/InputManager.h>

#include <GraphicsEngine/Drawers/MeshDrawer.h>
#include <GraphicsEngine/Buffers/BufferManager.h>
#include <Zultools/Timer.h>

#include <GraphicsEngine/Rendering/RenderPass/RenderPassManager.h>

std::unordered_map<std::string, void*> MainSingleton::mySingletons;
bool MainSingleton::myIsInitialized = false;


void MainSingleton::Setup()
{
	myIsInitialized = true;

	RegisterInstance<RenderPassManager>();

	RegisterInstance<Zengine::Buffers::BufferManager>();

	RegisterInstance<Zengine::Graphics::MeshDrawer>();

	RegisterInstance<CommonUtilities::Timer>();
}

const bool& MainSingleton::IsSetup() { return myIsInitialized; }