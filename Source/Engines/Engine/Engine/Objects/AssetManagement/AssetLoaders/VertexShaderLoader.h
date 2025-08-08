#pragma once

#include <Engine/Objects/AssetManagement/Assets/Shaders/VertexShader.h>

namespace Zengine
{
	class VertexShaderLoader
	{
	public:
		static void Load(const char* path, VertexShader& shader);

	private:
		static void LoadCompiledShader(const char* path, VertexShader& shader);
		static void LoadUncompiledShader(const char* path, VertexShader& shader);

		static void CreateInputLayout(const char* path, VertexShader& shader);
	};
}