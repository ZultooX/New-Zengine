#include "VertexShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

zg::shaders::VertexShader::VertexShader(const std::string& aShaderPath)
{
	myShaderPath = aShaderPath;
	Compile();
}

void zg::shaders::VertexShader::Compile()
{
	std::wstring wPath = std::wstring(myShaderPath.begin(), myShaderPath.end());
	ID3DBlob* shader = CompileShader(wPath.c_str(), "vs_5_0", "vs_main");

	DX11GraphicsEngine* ge =  (DX11GraphicsEngine * )Engine::GetGraphicsEngine();
	ge->GetDevice()->CreateVertexShader(shader->GetBufferPointer(), shader->GetBufferSize(), nullptr, &myShader);
}
