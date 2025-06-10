#pragma once

#include <unordered_map>
#include "Windows/Window.h"

class Engine;
class Editor {
public:
	static void Init();
	static void PreUpdate();
	static void Update();
	static void Render();

	static void OnResize();
	
	static void Save();

	template <typename T>
	static void OpenWindow();

private:
	static void UpdateMainMenuBar();

	static void OpenWindow(const std::string& aName, const int& aId);

private:
	static std::unordered_map<int, AbstractWindow*> IdToWindow;
};

template<typename T>
inline void Editor::OpenWindow()
{

}
