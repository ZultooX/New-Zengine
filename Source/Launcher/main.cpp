#define WIN32_LEAN_AND_MEAN
#define NOSOCKET   
#define NOMINMAX

#include <Windows.h>
#include <Shellapi.h>
#include <commdlg.h>
#include <string>
#include <Engine/Engine.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>
#include <assert.h>
#include <../Game/Game/GameWorld.h>

#define _CRT_SECURE_NO_WARNINGS

GameWorld gGameWorld;

HWND gHWND;
UINT gMESSAGE;
WPARAM gWPARAM;
LPARAM gLPARAM;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
	if (!Engine::Initialize())
	{
		assert(!"Engine initialization failed.");
	}

	const EngineSettings& engineSettings = Engine::GetSettings();


	WNDCLASSEXW wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszClassName = engineSettings.GetEngineName().c_str();

	RegisterClassExW(&wcex);

	gHWND = CreateWindow(
		engineSettings.GetEngineName().c_str(),
		engineSettings.GetWindowName().c_str(),
		//WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX,
		WS_OVERLAPPEDWINDOW | WS_POPUP,

		0,
		0,
		engineSettings.GetResolution().x,
		engineSettings.GetResolution().y,
		nullptr,
		nullptr,
		nullptr,
		nullptr);


	if (!gHWND)
	{
		return 0;
	}

	if (!Engine::LateInitialize())
	{
		assert(!"Engine initialization failed.");
	}

	gGameWorld.Init();

	ShowWindow(gHWND, nCmdShow);
	UpdateWindow(gHWND);

	MSG msg = {};
	bool shouldRun = true;
	while (shouldRun)
	{
		gGameWorld.Update();
		Engine::Update();

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				shouldRun = false;
			}
		}
	}

	return (int)msg.wParam;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	gHWND = hWnd;

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wparam, lparam))
		return true;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		Engine::Cleanup();
		break;

	default:
		return DefWindowProc(hWnd, message, wparam, lparam);
	}
	return 0;
}

int main()
{

}
