#include "Window.h"

const unsigned& AbstractWindow::GetID() { return myID; }
const unsigned& AbstractWindow::GetID() const { return myID; }

const std::string& AbstractWindow::GetWindowName() { return myWindowName; }
const std::string& AbstractWindow::GetWindowName() const { return myWindowName; }