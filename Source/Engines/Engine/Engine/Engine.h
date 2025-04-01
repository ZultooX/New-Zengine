#pragma once

#include <Engine/EngineSettings.h>

class IGraphicsAPI;
class Editor;

class Engine {
public:
	static bool Initialize();
	static bool LateInitialize();
	static bool Update();

	static void Cleanup();

public:
	static EngineSettings& GetSettings();
	static IGraphicsAPI* GetGraphicsEngine();

private:
	static bool PreUpdate();
	static bool MainUpdate();
	static bool PostUpdate();

	static EngineSettings Settings;

private:
	static IGraphicsAPI* GraphicsEngine;
};