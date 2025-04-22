#include "Shader.h"

#include <d3d11.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

#include <Engine/AssetManagement/VertexShaderManager.h>
#include <Engine/AssetManagement/PixelShaderManager.h>

#include <Engine/Utilities/MainSingleton.h>

namespace Zengine::Graphics
{
	Shader::Shader(const char* aVertexShader, const char* aPixelShader)
	{
		myVertexShader = MainSingleton::GetInstance<VertexShaderManager>().Get(aVertexShader);
		myPixelShader = MainSingleton::GetInstance<PixelShaderManager>().Get(aPixelShader);
	}

	void Shader::Bind()
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
		ge->GetContext()->PSSetShader(myPixelShader->GetShader(), nullptr, 0);
		ge->GetContext()->VSSetShader(myVertexShader->GetShader(), nullptr, 0);
	}

	void Shader::SetVertexShader(const char* aVertexShaderName)
	{
		myVertexShader = MainSingleton::GetInstance<VertexShaderManager>().Get(aVertexShaderName);
	}

	const VertexShader* Shader::GetVertexShader() const
	{
		return myVertexShader;
	}

	VertexShader* Shader::GetVertexShader()
	{
		return myVertexShader;
	}
	
	void Shader::SetPixelShader(const char* aPixelShaderName)
	{
		myPixelShader = MainSingleton::GetInstance<PixelShaderManager>().Get(aPixelShaderName);
	}
	
	const PixelShader* Shader::GetPixelShader() const
	{
		return myPixelShader;
	}

	PixelShader* Shader::GetPixelShader()
	{
		return myPixelShader;
	}
}