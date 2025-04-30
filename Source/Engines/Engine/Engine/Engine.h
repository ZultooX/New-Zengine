#pragma once

#include <Engine/EngineSettings.h>

#include <Engine/NetworkManager.h>

class IGraphicsAPI;
class Editor;


class Engine {
public:
	static bool Initialize();
	static bool LateInitialize();
	static bool Update();

	static bool OnResize(const int& aWidth, const int& aHeight);

	static void Cleanup();

public:
	static EngineSettings& GetSettings();
	static IGraphicsAPI* GetGraphicsEngine();
	static NetworkManager& GetNetworkManager();

private:
	static bool PreUpdate();
	static bool MainUpdate();
	static bool PostUpdate();

	static EngineSettings Settings;

private:
	static IGraphicsAPI* GraphicsEngine;
	static NetworkManager networkManager;
};