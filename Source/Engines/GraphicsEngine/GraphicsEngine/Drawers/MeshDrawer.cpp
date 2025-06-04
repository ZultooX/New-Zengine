#include "MeshDrawer.h"

#include <Engine/Editor/DebugLogger.h>
#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <GraphicsEngine/GraphicsStructs.h>
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Assets/Material.h>
#include <Engine/AssetManagement/Assets/Texture.h>
#include <Engine/AssetManagement/Assets/PixelShader.h>
#include <Engine/AssetManagement/Assets/VertexShader.h>
#include <Engine/Utilities/MainSingleton.h>

namespace Zengine::Graphics
{
	void MeshDrawer::Draw(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer)
	{
		//DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();


		//for (const std::string& materialPath : aMeshrenderer->GetMaterials())
		//{
		//	Material* material = MainSingleton::GetInstance<MaterialManager>().Get(materialPath);
		//	
		//	for(const TextureData& textureData : material->GetTexture())
		//	{ 
		//		Texture* texture = MainSingleton::GetInstance<TextureManager>().Get(textureData.texturePath);

		//		ge->GetContext()->PSSetShaderResources(textureData.bindSlot, 1, texture->GetSRVAddress());
		//	}


		//}




		//Draw(aMeshrenderer, nullptr, aMeshrenderer->GetVertexShader());
	}

	void MeshDrawer::Draw(AssetPointer<Mesh>& aMesh, PixelShader* aPixelShader, VertexShader* aVertexShader)
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		ge->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ge->GetContext()->IASetInputLayout(aVertexShader->GetInputLayout());

		ge->GetContext()->PSSetShader(aPixelShader->GetShader(), nullptr, 0);
		ge->GetContext()->VSSetShader(aVertexShader->GetShader(), nullptr, 0);

		constexpr unsigned int stride = sizeof(Vertex);
		constexpr unsigned int offset = 0;

		ge->GetContext()->IASetVertexBuffers(0, 1, aMesh->GetVertexBufferAddr(), &stride, &offset);
		ge->GetContext()->IASetIndexBuffer(aMesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		ge->GetContext()->DrawIndexed(aMesh->GetIndicies().size(), 0, 0);

		ge->UpdateDrawCalls();
	}
	void MeshDrawer::BindMaterial(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer, const unsigned& aIdx)
	{
		// CONTINUE
	}
}