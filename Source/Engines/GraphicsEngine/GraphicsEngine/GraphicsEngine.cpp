#include "GraphicsEngine.h"


bool IGraphicsAPI::Update()
{
	if (!PreUpdate()) return false;
	if (!MainUpdate()) return false;
	if (!PostUpdate()) return false;

	return true;
}

void IGraphicsAPI::UpdateDrawCalls() { ++myDrawCalls; }
void IGraphicsAPI::UpdateDrawCalls(const int& anAmount) { myDrawCalls += anAmount; }
void IGraphicsAPI::ClearDrawCalls() { myDrawCalls = 0; }
const int& IGraphicsAPI::GetDrawCalls() const { return myDrawCalls; }
