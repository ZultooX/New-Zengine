#pragma once

#include <string>

namespace Zengine::Graphics
{
	class PixelShader;

	class FullscreenSprite final {
	public:
		void Render();

		void SetPixelShader(const std::string& aPixelShaderPath);

	private:
		std::string myPixelShaderPath;
	};
}