#pragma once

#include <Engine/Objects/AssetManagement/Assets/Shaders/PixelShader.h>

namespace Zengine
{
	class PixelShaderLoader
	{
	public:
		static void Load(const char* path, PixelShader& shader);

	private:
		static void LoadCompiledShader(const char* path, PixelShader& shader);
		static void LoadUncompiledShader(const char* path, PixelShader& shader);
	};
}