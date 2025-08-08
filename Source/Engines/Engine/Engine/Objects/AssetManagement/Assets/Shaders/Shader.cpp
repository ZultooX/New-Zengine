#include "Shader.h"

namespace Zengine
{
	template<typename ShaderType>
	Shader<ShaderType>::Shader(const std::string& _ShaderFilePath)
		: Asset(), shaderFilePath(_ShaderFilePath), shader(nullptr) {}

	template<typename ShaderType>
	Shader<ShaderType>::Shader()
		: Asset(), shaderFilePath(""), shader(nullptr) {}

	template<typename ShaderType>
	Shader<ShaderType>::Shader(const size_t& _id)
		: Asset(_id), shader(nullptr) {}


	template<typename ShaderType>
	const std::string& Shader<ShaderType>::GetShaderData() { return shaderData; }

	template<typename ShaderType>
	void Shader<ShaderType>::SetShaderData(const std::string& _shaderData) { shaderData = _shaderData; }

	template<typename ShaderType>
	const std::string& Shader<ShaderType>::GetShaderFilePath() { return shaderFilePath; }

	template<typename ShaderType>
	void Shader<ShaderType>::SetShaderFilePath(const std::string& _shaderFilePath) { shaderFilePath = _shaderFilePath; }

	template<typename ShaderType>
	ShaderType* Shader<ShaderType>::GetShader(){return shader;}

	template<typename ShaderType>
	ShaderType** Shader<ShaderType>::GetShaderAddr(){return &shader;}
}