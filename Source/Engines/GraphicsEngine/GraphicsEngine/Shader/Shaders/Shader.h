#pragma once

#include "VertexShader.h"
#include "PixelShader.h"

namespace zg
{
	namespace shaders
	{
		/// <summary>
		/// This shader class stores both pixel and vertex shader.
		/// </summary>
		class Shader final
		{
		public:
			Shader(const std::string& aVertexShader, const std::string& aPixelShader);

			void Bind();

		private:
			PixelShader* myPixelShader;
			VertexShader* myVertexShader;
		};
	}
}