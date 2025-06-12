#include "FullscreenSprite.h"

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#include <Engine/Utilities/MainSingleton.h>
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Assets/VertexShader.h>

namespace Zengine::Graphics
{
	FullscreenSprite::FullscreenSprite(const std::string& aPixelShaderPath) : myPixelShaderPath(aPixelShaderPath)
	{
		myPS = AssetManager::GetFromPath<PixelShader>(myPixelShaderPath.c_str());
		myVS = AssetManager::GetFromPath<VertexShader>(ZENGINE_VERTEX_SHADERS_PATH"VS_FullscreenEffect.cso");
	}

	void FullscreenSprite::Render()
	{
		if (myPixelShaderPath.empty()) return;



		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
		ge->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
		ge->GetContext()->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
		ge->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ge->GetContext()->IASetInputLayout(nullptr);

		ge->GetContext()->PSSetShader(myPS->GetShader(), nullptr, 0);
		ge->GetContext()->VSSetShader(myVS->GetShader(), nullptr, 0);

		ge->GetContext()->Draw(3, 0);
	}

	void FullscreenSprite::SetPixelShader(const std::string& aPixelShaderPath) { myPixelShaderPath = aPixelShaderPath; }
}
