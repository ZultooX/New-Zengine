#include "RenderingDebuggerWindow.h"

#include <Zultools/Random.h>
#include <string>
#include <ImGui/imgui.h>
#include <Engine/Editor/DebugLogger.h>

#include <Engine/Utilities/MainSingleton.h>
#include <GraphicsEngine/Rendering/RenderPass/RenderPassManager.h>
#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#include <Zultools/Timer.h>

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

	DrawImage("world Position",		{ 250, 250 }, { 0, 0 },		{ 5, 20 }, gbuffer.GetSRV(GBuffer::GBufferTexture::WorldPosition).Get());
	DrawImage("Albedo",				{ 250, 250 }, { 250, 0 },	{ 10, 20 }, gbuffer.GetSRV(GBuffer::GBufferTexture::Albedo).Get());
	DrawImage("Normal",				{ 250, 250 }, { 500, 0 },	{ 15, 20 }, gbuffer.GetSRV(GBuffer::GBufferTexture::Normal).Get());
	DrawImage("Material",			{ 250, 250 }, { 750, 0 },	{ 20, 20 }, gbuffer.GetSRV(GBuffer::GBufferTexture::Material).Get());
	DrawImage("Ambient Occlusion",	{ 250, 250 }, { 1000, 0 },	{ 25, 20 }, gbuffer.GetSRV(GBuffer::GBufferTexture::AmbientOcclusionAndCustom).Get());

	const DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	CommonUtilities::Timer& timer = MainSingleton::GetInstance<CommonUtilities::Timer>();

	int drawCalls = ge->GetDrawCalls();
	float delta = timer.GetDeltaTime();
	float fps = 1.f / delta;
	ImGui::Text((std::string("Draw calls: ") + std::to_string(drawCalls)).c_str());
	ImGui::Text((std::string("Deltatime: ") + std::to_string(delta)).c_str());
	ImGui::Text((std::string("FPS: ") + std::to_string(fps)).c_str());
}

void RenderingDebuggerWindow::Close()
{
}

void RenderingDebuggerWindow::DrawImage(const char* aTitle, const ImVec2& aSize, const ImVec2& aOffset, const ImVec2& padding, ID3D11ShaderResourceView* aImage)
{
	const ImVec2 position = ImVec2(aOffset.x + padding.x, aOffset.y + padding.y);
	ImGui::SetCursorPos(position);


	ImGui::Text(aTitle);
	const ImVec2 textSize = ImGui::CalcTextSize(aTitle);

	ImGui::SetCursorPos(ImVec2(position.x, position.y + textSize.y));
	const ImVec2 imagePos = ImGui::GetCursorScreenPos();
	ImGui::Image(aImage, aSize);

	DrawSquare(aSize, imagePos, padding);
}

void RenderingDebuggerWindow::DrawSquare(const ImVec2& aSize, const ImVec2& aOffset, const ImVec2& padding)
{
	ImVec2 topLeft = ImVec2(aOffset.x, aOffset.y);
	ImVec2 bottomRight = ImVec2(aOffset.x + aSize.x, aOffset.y + aSize.y);

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	const ImColor color = IM_COL32(100, 100, 100, 255);

	drawList->AddRect(topLeft, bottomRight, color, 0);
}
