#pragma once

#include <Engine/Objects/AssetManagement/Assets/Shaders/Shader.h>

#include <string>

struct ID3D11PixelShader;
namespace Zengine
{
	class PixelShader : public virtual Shader<ID3D11PixelShader>
	{
	public:
		PixelShader(const std::string& _ShaderFilePath);

		PixelShader();
		PixelShader(const size_t& _id);
		virtual ~PixelShader() = default;

	public:
		void Compile() override;
		void Bind(const unsigned& slot) override;
	};
}