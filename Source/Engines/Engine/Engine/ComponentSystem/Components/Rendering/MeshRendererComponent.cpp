#include "MeshRendererComponent.h"

#include <Engine/Utilities/MainSingleton.h>
#include <Engine/AssetManagement/MeshManager.h>

namespace Zengine::ComponentSystem
{
	void MeshRenderer::SetVertexShader(const char* aVertexShaderName) { myShader.SetVertexShader(aVertexShaderName); }
	void MeshRenderer::SetPixelShader(const char* aPixelShaderName)   { myShader.SetPixelShader(aPixelShaderName); }

	void MeshRenderer::SetMesh(const char* aMeshName)
	{
		myMesh = MainSingleton::GetInstance<MeshManager>().Get(aMeshName);
	}

	Mesh* MeshRenderer::GetMesh() const { return myMesh; }
	const Zengine::Graphics::PixelShader* MeshRenderer::GetPixelShader()const
	{
		return myShader.GetPixelShader();
	}
	Zengine::Graphics::PixelShader* MeshRenderer::GetPixelShader()
	{
		return myShader.GetPixelShader();
	}
	Zengine::Graphics::VertexShader* MeshRenderer::GetVertexShader()
	{
		return myShader.GetVertexShader();
	}
	const Zengine::Graphics::VertexShader* MeshRenderer::GetVertexShader()const
	{
		return myShader.GetVertexShader();
	}
	void MeshRenderer::SetTexture(const std::string& aTexturePath, TextureSlot aSlot)
	{
		myTextures[aSlot] = aTexturePath;
	}
	std::string* MeshRenderer::GetTextures()
	{
		return myTextures;
	}
}