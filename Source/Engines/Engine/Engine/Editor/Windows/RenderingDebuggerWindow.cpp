#include "RenderingDebuggerWindow.h"

#include <Zultools/Random.h>
#include <ImGui/imgui.h>
#include <Engine/Editor/DebugLogger.h>

#include <Engine/Utilities/MainSingleton.h>
#include <GraphicsEngine/DX11/Rendering/RenderPass/RenderPassManager.h>

RenderingDebuggerWindow::RenderingDebuggerWindow(const int& aId)
{
	myWindowName = "Rendering Debugger";
	myID = aId == -1 ? Random::GetValue<int>() : aId;
}

void RenderingDebuggerWindow::Open()
{

}

void RenderingDebuggerWindow::Update()
{
	RenderPassManager& rpm = MainSingleton::GetInstance<RenderPassManager>();
	GBuffer& gbuffer = rpm.GetBasePass().GetGBuffer();

	ImGui::Image(gbuffer.GetSRV(GBuffer::GBufferTexture::WorldPosition).Get(), {500, 500});
	ImGui::Image(gbuffer.GetSRV(GBuffer::GBufferTexture::Albedo).Get(), {500, 500});
	ImGui::Image(gbuffer.GetSRV(GBuffer::GBufferTexture::Normal).Get(), {500, 500});
	ImGui::Image(gbuffer.GetSRV(GBuffer::GBufferTexture::Material).Get(), {500, 500});
	ImGui::Image(gbuffer.GetSRV(GBuffer::GBufferTexture::AmbientOcclusionAndCustom).Get(), {500, 500});
}

void RenderingDebuggerWindow::Close()
{
}
