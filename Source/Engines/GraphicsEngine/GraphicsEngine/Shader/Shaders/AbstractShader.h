#pragma once

#include <string>
#include <d3d11.h>

namespace zg
{
	namespace shaders
	{
		template<typename T>
		class AbstractShader
		{
		public:
			AbstractShader() = default;
			~AbstractShader() = default;


			ID3DBlob* CompileShader(const wchar_t* aPath, const char* aShaderModel, const std::string& aEntryPoint);

			const T* GetShader() const;
			T* GetShader();

		protected:
			virtual void Compile() = 0;

		protected:
			std::string myShaderPath;
			T* myShader;
		};
	}
}