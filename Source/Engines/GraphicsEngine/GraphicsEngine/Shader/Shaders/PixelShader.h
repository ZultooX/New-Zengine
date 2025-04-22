#pragma once

#include "AbstractShader.h"
#include <GraphicsEngine/Shader/ShaderReflection.h>

namespace Zengine::Graphics
{
	class PixelShader final : public AbstractShader<ID3D11PixelShader>
	{
	public:
		PixelShader(const char* aShaderPath);

		void Compile() override;

	private:
		ShaderData myShaderData;
	};
}