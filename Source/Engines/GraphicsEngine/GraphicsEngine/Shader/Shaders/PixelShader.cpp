#include "PixelShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>
#include <filesystem>
#include <GraphicsEngine/Shader/ShaderReflection.h>
#include <fstream>

namespace Zengine::Graphics
{
	PixelShader::PixelShader(const char* aShaderPath)
	{
		myShaderPath = aShaderPath;

		if (std::filesystem::path(aShaderPath).extension().string() == ".cso")
		{
			DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
			std::ifstream psFile;
			psFile.open(aShaderPath, std::ios::binary);
			std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
			HRESULT result = ge->GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &myShader);
		}
		else
		{
			Compile();
		}
	}

	void PixelShader::Compile()
	{
		std::wstring wPath = std::wstring(myShaderPath.begin(), myShaderPath.end());
		ID3DBlob* shader = Compiler::CompileShader(wPath.c_str(), "ps_5_0", "ps_main");

		//myShaderData = ShaderReflection::ReflectShader(shader);


	}
}