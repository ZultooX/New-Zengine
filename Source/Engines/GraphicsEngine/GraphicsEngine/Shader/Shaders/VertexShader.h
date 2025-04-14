#pragma once

#include "AbstractShader.h"

namespace zg
{
	namespace shaders
	{
		class VertexShader final : public AbstractShader<ID3D11VertexShader>
		{
		public:
			VertexShader(const std::string& aShaderPath);

			void Compile() override;
		};
	}
}