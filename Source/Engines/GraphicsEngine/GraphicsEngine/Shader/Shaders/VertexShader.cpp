#include "VertexShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

#include <GraphicsEngine/InputLayoutManager.h>

#include <filesystem>
#include <fstream>

namespace Zengine::Graphics
{
	VertexShader::VertexShader(const char* aShaderPath, const char* aInputLayout) : myInputLayoutName(aInputLayout)
	{
		myShaderPath = aShaderPath;
		
		if (std::filesystem::path(aShaderPath).extension().string() == ".cso")
		{
			DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
			std::ifstream psFile;
			psFile.open(aShaderPath, std::ios::binary);
			std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
			HRESULT result = ge->GetDevice()->CreateVertexShader(psData.data(), psData.size(), nullptr, &myShader);

			myInputLayout = InputLayoutManager::CreateOrGet(myInputLayoutName, InputLayoutManager::GetDefaultInputLayoutDesc(), psData.data(), psData.size());
		}
		else
		{
			Compile();
		}
	}

	void VertexShader::Compile()
	{
		std::wstring wPath = std::wstring(myShaderPath.begin(), myShaderPath.end());
		ID3DBlob* shader = Compiler::CompileShader(wPath.c_str(), "vs_5_0", "vs_main");

		myInputLayout = InputLayoutManager::CreateOrGet(myInputLayoutName, InputLayoutManager::GetDefaultInputLayoutDesc(), shader->GetBufferPointer(), shader->GetBufferSize());

		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
		ge->GetDevice()->CreateVertexShader(shader->GetBufferPointer(), shader->GetBufferSize(), nullptr, &myShader);
	}

	const ID3D11InputLayout* VertexShader::GetInputLayout() const { return myInputLayout; }
	ID3D11InputLayout* VertexShader::GetInputLayout() { return myInputLayout; }
}