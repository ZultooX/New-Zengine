#pragma once

#include "AbstractShader.h"

struct ID3D11InputLayout;
struct ID3D11VertexShader;
namespace Zengine::Graphics
{
	class VertexShader final : public AbstractShader<ID3D11VertexShader>
	{
	public:
		VertexShader(const char* aShaderPath, const char* aInputLayout = "Default");

		void Compile() override;

		const ID3D11InputLayout* GetInputLayout() const; 
		ID3D11InputLayout* GetInputLayout(); 

	private:
		ID3D11InputLayout* myInputLayout;
		const char* myInputLayoutName;
	};
}