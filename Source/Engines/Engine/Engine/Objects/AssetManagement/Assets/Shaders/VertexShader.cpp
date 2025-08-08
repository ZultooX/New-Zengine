#include "VertexShader.h"


#include <d3d11.h>
namespace Zengine
{
	VertexShader::VertexShader(const std::string& _ShaderFilePath)
		: Shader(_ShaderFilePath) {}

	VertexShader::VertexShader()
		: Shader() {}

	VertexShader::VertexShader(const size_t& _id)
		: Shader(_id) {}

	ID3D11InputLayout* VertexShader::GetInputLayout() { return inputLayout; }
	ID3D11InputLayout** VertexShader::GetInputLayoutAddr() { return &inputLayout; }

	void VertexShader::Compile()
	{
	}

	void VertexShader::Bind(const unsigned& slot)
	{
	}
}