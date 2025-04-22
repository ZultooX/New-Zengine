#pragma once

#include "VertexShader.h"
#include "PixelShader.h"

namespace Zengine::Graphics
{
	/// <summary>
	/// This shader class stores both pixel and vertex shader.
	/// </summary>
	class Shader final
	{
	public:
		Shader() = default;
		Shader(const char* aVertexShader, const char* aPixelShader);

		void Bind();

		void SetVertexShader(const char* aVertexShaderName);
		const VertexShader* GetVertexShader() const;
		VertexShader* GetVertexShader();
		
		void SetPixelShader(const char* aPixelShaderName);
		const PixelShader* GetPixelShader() const;
		PixelShader* GetPixelShader() ;

	private:
		PixelShader* myPixelShader;
		VertexShader* myVertexShader;
	};
}