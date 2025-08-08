#include "PixelShaderLoader.h"

#include <unordered_map>
#include <fstream>
#include <d3d11.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

namespace Zengine
{
	void PixelShaderLoader::Load(const char* path, PixelShader& shader)
	{
	}

	void PixelShaderLoader::LoadCompiledShader(const char* path, PixelShader& shader)
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		std::ifstream psFile;
		psFile.open(path, std::ios::binary);
		std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
		HRESULT result = ge->GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, shader.GetShaderAddr());

		psFile.close();
	}

	void PixelShaderLoader::LoadUncompiledShader(const char* path, PixelShader& shader)
	{
	}
}