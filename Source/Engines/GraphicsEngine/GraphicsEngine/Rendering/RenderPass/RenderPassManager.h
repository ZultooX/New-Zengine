#pragma once

#include <GraphicsEngine/IO/RenderTarget.h>
#include <GraphicsEngine/Rendering/RenderPass/Passes/BasePass.h>
#include <GraphicsEngine/Rendering/RenderPass/Passes/LightPass.h>
#include <GraphicsEngine/Rendering/RenderPass/Passes/ForwardPass.h>

class RenderPassManager
{
public:
	RenderPassManager() = default;

public:
	void Init();
	void Render();

	RenderTarget& GetRTV();

public:
	BasePass& GetBasePass() { return myBasePass; }
	LightPass& GetLightPass() { return myLightPass; }
	ForwardPass& GetForwardPass() { return myForwardPass; }

private:
	RenderTarget myRTV;

private:
	BasePass myBasePass;
	LightPass myLightPass;
	ForwardPass myForwardPass;
};