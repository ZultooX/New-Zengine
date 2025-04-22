#pragma once

#include <GraphicsEngine/DX11/IO/RenderTarget.h>
#include <GraphicsEngine/DX11/Rendering/RenderPass/Passes/BasePass.h>
#include <GraphicsEngine/DX11/Rendering/RenderPass/Passes/LightPass.h>

class RenderPassManager
{
public:
	void Init();
	void Render();

	RenderTarget& GetRTV();

public:
	BasePass& GetBasePass() { return myBasePass; }

private:
	RenderTarget myRTV;

private:
	BasePass myBasePass;
	LightPass myLightPass;
};