#pragma once

#include <string>
#include <Engine/AssetManagement/Base/AssetPointer.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Assets/VertexShader.h>


namespace Zengine::Graphics
{

	class FullscreenSprite final {
	public:
		FullscreenSprite() = default;
		FullscreenSprite(const std::string& aPixelShaderPath);
		void Render();

		void SetPixelShader(const std::string& aPixelShaderPath);

	private:
		AssetPointer<VertexShader> myVS;
		AssetPointer<PixelShader> myPS;

		std::string myPixelShaderPath;
	};
}