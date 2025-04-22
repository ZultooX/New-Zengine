#include "FullscreenSprite.h"

#include <GraphicsEngine/Shader/Shaders/PixelShader.h>
#include <GraphicsEngine/Shader/Shaders/VertexShader.h>
#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#include <Engine/Utilities/MainSingleton.h>
#include <Engine/AssetManagement/PixelShaderManager.h>
#include <Engine/AssetManagement/VertexShaderManager.h>

namespace Zengine::Graphics
{
	void FullscreenSprite::Render()
	{
		if (myPixelShaderPath.empty()) return;

		PixelShader* ps = MainSingleton::GetInstance<PixelShaderManager>().Get(myPixelShaderPath);
		VertexShader* vs = MainSingleton::GetInstance<VertexShaderManager>().Get(ZENGINE_SHADERS_PATH"VS_FullscreenEffect.cso");

		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
		ge->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
		ge->GetContext()->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
		ge->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ge->GetContext()->IASetInputLayout(nullptr);

		ge->GetContext()->PSSetShader(ps->GetShader(), nullptr, 0);
		ge->GetContext()->VSSetShader(vs->GetShader(), nullptr, 0);

		ge->GetContext()->Draw(3, 0);
	}

	void FullscreenSprite::SetPixelShader(const std::string& aPixelShaderPath) { myPixelShaderPath = aPixelShaderPath; }
}
