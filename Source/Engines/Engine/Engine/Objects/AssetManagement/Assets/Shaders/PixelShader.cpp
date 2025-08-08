#include "PixelShader.h"

namespace Zengine
{
	PixelShader::PixelShader(const std::string& _ShaderFilePath)
		: Shader(_ShaderFilePath) {}

	PixelShader::PixelShader()
		: Shader() {}

	PixelShader::PixelShader(const size_t& _id)
		: Shader(_id) {}

	void PixelShader::Compile()
	{
	}

	void PixelShader::Bind(const unsigned& slot)
	{
	}
}