#pragma once

#include "AbstractShader.h"
#include <GraphicsEngine/Shader/ShaderReflection.h>

namespace zg
{
	namespace shaders
	{
		class PixelShader final : public AbstractShader<ID3D11PixelShader>
		{
		public:
			PixelShader(const std::string& aShaderPath);

			void Compile() override;

		private:
			ShaderData myShaderData;
		};
	}
}