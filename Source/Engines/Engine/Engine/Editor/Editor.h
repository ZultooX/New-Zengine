#pragma once

#include <unordered_map>
#include "Windows/Window.h"

class Engine;
class Editor {
public:
	static void Init();
	static void Update();
	static void Render();
	
	template <typename T>
	static void OpenWindow();

private:
	static void UpdateMainMenuBar();

private:
	static std::unordered_map<unsigned, AbstractWindow*> IdToWindow;
};

template<typename T>
inline void Editor::OpenWindow()
{

}
