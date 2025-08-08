#pragma once

#include <Engine/Objects/AssetManagement/Base/Asset.h>

#include <string>

namespace Zengine
{
	template<typename ShaderType>
	class Shader : public virtual Asset
	{
	public:
		Shader(const std::string& _ShaderFilePath);

		Shader();
		Shader(const size_t& _id);
		virtual ~Shader() = default;

	public:
		const std::string& GetShaderData();
		void SetShaderData(const std::string& _shaderData);

		const std::string& GetShaderFilePath();
		void SetShaderFilePath(const std::string& _shaderFilePath);

		ShaderType* GetShader();
		ShaderType** GetShaderAddr();

	public:
		virtual void Compile() = 0;
		virtual void Bind(const unsigned& slot) = 0;

	protected:
		ShaderType* shader;
		std::string shaderFilePath;
		std::string shaderData;
	};
}