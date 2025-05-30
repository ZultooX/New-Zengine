#include "Engine.h"

#include <Engine/Files/MetaFileRegistry.h>
#include <Engine/Utilities/MainSingleton.h>
#include <Zultools/Timer.h>
#include <ComponentSystem/GameObjectManager.h>
#include <ComponentSystem/ComponentManager.h>
#include <Engine/EngineSettings.h>
#include <GraphicsEngine/GraphicsEngine.h>

#include <External/nlohmann/json.hpp>

#ifdef _DEBUG
#include <Editor/Editor.h>
#include <ImGui/imgui.h>
#endif

#include <fstream>
#include <string>

#include <Client.h>
#include <Engine/AssetManagement/AssetManager.h>

EngineSettings Engine::Settings;
NetworkManager Engine::networkManager;
IGraphicsAPI* Engine::GraphicsEngine;

bool Engine::Initialize()
{
	Settings.Load();

	MetaFileRegistry::ValidateFiles();
	MetaFileRegistry::Load();

	MainSingleton::Setup();
	networkManager.Init();

	return true;
}

bool Engine::LateInitialize()
{
#ifdef USE_DX11
	GraphicsEngine = new DX11GraphicsEngine();
#elif USE_OPENGL
	GraphicsEngine = new OpenGLGraphicsEngine();
#endif // USE_DX11

	if (!GraphicsEngine->Initialize()) return false;

#ifdef _DEBUG
	Editor::Init();
#endif

	int age = MetaFileRegistry::GetMetaData<int>("This Cool path", "age");
	MetaFileRegistry::SetMetaData("This Cool path", "name", "Simon");

	return true;
}

bool Engine::Update()
{
	if (!PreUpdate()) return false;
	if (!MainUpdate()) return false;
	if (!PostUpdate()) return false;

	return true;
}

bool Engine::OnResize(const int& aWidth, const int& aHeight)
{
	if (!GraphicsEngine) return false;

	EngineSettings& settings = Engine::GetSettings();
	settings.SetResolution({ aWidth, aHeight });

	GraphicsEngine->OnResize();
	Editor::OnResize();

	return true;
}

void Engine::Cleanup()
{
	MetaFileRegistry::Unload();

#ifdef _DEBUG
	Editor::Save();
#endif
}


bool Engine::PreUpdate()
{
	Zengine::ComponentSystem::GameObjectManager::BeginFrame();
#ifdef _DEBUG
	Editor::PreUpdate();
	Editor::Update();
#endif

	MainSingleton::GetInstance<CommonUtilities::Timer>().Update();



	Zengine::ComponentSystem::ComponentManager::UpdateManager();

	GraphicsEngine->Update();

	return true;
}

bool Engine::MainUpdate()
{
	networkManager.Update();

	return true;
}

bool Engine::PostUpdate()
{
#ifdef _DEBUG
	Editor::Render();
#endif

	GraphicsEngine->Present();
	return true;
}


EngineSettings& Engine::GetSettings() { return Settings; }
IGraphicsAPI* Engine::GetGraphicsEngine() { return GraphicsEngine; }
NetworkManager& Engine::GetNetworkManager() { return networkManager; }