#include "PixelShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

#include <GraphicsEngine/Shader/ShaderReflection.h>

zg::shaders::PixelShader::PixelShader(const std::string& aShaderPath)
{
	myShaderPath = aShaderPath;
	Compile();
}

void zg::shaders::PixelShader::Compile()
{
	std::wstring wPath = std::wstring(myShaderPath.begin(), myShaderPath.end());
	ID3DBlob* shader = CompileShader(wPath.c_str(), "ps_5_0", "ps_main");

	myShaderData = ShaderReflection::ReflectShader(shader);

	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ge->GetDevice()->CreatePixelShader(shader->GetBufferPointer(), shader->GetBufferSize(), nullptr, &myShader);
}