#include "Engine.h"
#include <Engine/Files/MetaFileRegistry.h>

#include <External/nlohmann/json.hpp>
#include <fstream>
#include <string>

#include <Engine/EngineSettings.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Editor/Editor.h>

#include <ImGui/imgui.h>

#include <Engine/AssetManagement/MeshManager.h>
#include <Engine/Utilities/MainSingleton.h>

#include <Zultools/Timer.h>
#include <ComponentSystem/ComponentManager.h>

EngineSettings Engine::Settings;
IGraphicsAPI* Engine::GraphicsEngine;

bool Engine::Initialize()
{
	Settings.Load();

	MetaFileRegistry::ValidateFiles();
	MetaFileRegistry::Load();

	MainSingleton::Setup();

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

	Editor::Init();

	return true;
}

bool Engine::Update()
{
	if (!PreUpdate()) return false;
	if (!MainUpdate()) return false;
	if (!PostUpdate()) return false;

	return true;
}

void Engine::Cleanup()
{
	MetaFileRegistry::Unload();
}


bool Engine::PreUpdate()
{
	Editor::PreUpdate();
	MainSingleton::GetInstance<CommonUtilities::Timer>().Update();
	Zengine::ComponentSystem::ComponentManager::UpdateManager();

	GraphicsEngine->Update();
	Editor::Update();

	return true;
}

bool Engine::MainUpdate()
{
	return true;
}

bool Engine::PostUpdate()
{
	Editor::Render();
	GraphicsEngine->Present();
	return true;
}


EngineSettings& Engine::GetSettings() { return Settings; }
IGraphicsAPI* Engine::GetGraphicsEngine() { return GraphicsEngine; }
