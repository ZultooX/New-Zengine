#pragma once

#include <string>
#include <d3d11.h>

namespace Zengine::Graphics
{
	template<typename T>
	class AbstractShader
	{
	public:
		AbstractShader() = default;
		~AbstractShader() = default;

		const T* GetShader() const;
		T* GetShader();

		inline const std::string& GetPath() { return myShader; }

	protected:
		virtual void Compile() = 0;

	protected:
		std::string myShaderPath;
		T* myShader;
	};

	namespace Compiler {
		ID3DBlob* CompileShader(const wchar_t* aPath, const char* aShaderModel, const std::string& aEntryPoint);
	}

	template<typename T>
	T* AbstractShader<T>::GetShader() { return myShader; }

	template<typename T>
	const T* AbstractShader<T>::GetShader() const { return myShader; }
}