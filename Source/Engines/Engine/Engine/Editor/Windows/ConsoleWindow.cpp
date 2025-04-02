#include "ConsoleWindow.h"

#include <Zultools/Random.h>

ConsoleWindow::ConsoleWindow()
{
	myWindowName = "Console";
	myID = Random::GetValue<unsigned>();
}

void ConsoleWindow::Open()
{
}

void ConsoleWindow::Update()
{
}

void ConsoleWindow::Close()
{
}
