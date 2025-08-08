#pragma once

#include <Engine/Objects/AssetManagement/Assets/Shaders/Shader.h>

#include <string>

struct ID3D11VertexShader;
struct ID3D11InputLayout;
namespace Zengine
{
	class VertexShader : public virtual Shader<ID3D11VertexShader>
	{
	public:
		VertexShader(const std::string& _ShaderFilePath);

		VertexShader();
		VertexShader(const size_t& _id);
		virtual ~VertexShader() = default;

	public:
		void Compile() override;
		void Bind(const unsigned& slot) override;

	public:
		ID3D11InputLayout* GetInputLayout();
		ID3D11InputLayout** GetInputLayoutAddr();

	private:
		ID3D11InputLayout* inputLayout;
	};
}