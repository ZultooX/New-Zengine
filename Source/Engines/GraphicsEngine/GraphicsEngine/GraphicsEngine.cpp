#include "GraphicsEngine.h"


bool IGraphicsAPI::Update()
{
	if (!PreUpdate()) return false;
	if (!MainUpdate()) return false;
	if (!PostUpdate()) return false;

	return true;
}