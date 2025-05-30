#include "RenderPassManager.h"

void RenderPassManager::Init()
{
	myBasePass.Start();
	myLightPass.Start();
}

void RenderPassManager::Render()
{
	myBasePass.Render();
	myLightPass.Render(myBasePass.GetGBuffer());
	myForwardPass.Render();
}

RenderTarget& RenderPassManager::GetRTV() { return myRTV; }
