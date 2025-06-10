#pragma once

#include <Engine/EngineSettings.h>

#include <Engine/NetworkManager.h>
#include <windows.h>
#include <Zultools/Input/InputMapper.h>

class IGraphicsAPI;
class Editor;


class Engine {
public:
	static bool Initialize();
	static bool LateInitialize();
	static void ProcessMessage(const HWND& aHwnd, const UINT& aMessage, const WPARAM& aWparam, const LPARAM& aLparam);

	static bool OnResize(const int& aWidth, const int& aHeight);

	static void Cleanup();

public:
	static EngineSettings& GetSettings();
	static IGraphicsAPI* GetGraphicsEngine();
	static NetworkManager& GetNetworkManager();
	static InputMapper& GetInputMapper();

#pragma region [UPDATE]

public:
	static bool Update();

private:
	static bool PreUpdate();
	static bool MainUpdate();
	static bool PostUpdate();

#pragma endregion

private:
	static EngineSettings Settings;

	static IGraphicsAPI* GraphicsEngine;
	static NetworkManager networkManager;

	static UINT message;
	static WPARAM Wparam;
	static LPARAM Lparam;

	static InputMapper mapper;
};