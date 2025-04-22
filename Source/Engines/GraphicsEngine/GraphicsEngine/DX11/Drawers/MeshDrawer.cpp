#include "MeshDrawer.h"

#include <Engine/Editor/DebugLogger.h>
#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <GraphicsEngine/GraphicsStructs.h>

namespace Zengine::Graphics
{
	void MeshDrawer::Draw(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer)
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		Draw(aMeshrenderer, aMeshrenderer->GetPixelShader(), aMeshrenderer->GetVertexShader());
	}

	void MeshDrawer::Draw(Zengine::ComponentSystem::MeshRenderer* aMeshrenderer, PixelShader* aPixelShader, VertexShader* aVertexShader)
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		ge->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ge->GetContext()->IASetInputLayout(aMeshrenderer->GetVertexShader()->GetInputLayout());

		ge->GetContext()->PSSetShader(aPixelShader->GetShader(), nullptr, 0);
		ge->GetContext()->VSSetShader(aVertexShader->GetShader(), nullptr, 0);

		const Mesh* mesh = aMeshrenderer->GetMesh();
		for (const SubMesh& sub : mesh->meshes)
		{
			constexpr unsigned int stride = sizeof(Vertex);
			constexpr unsigned int offset = 0;

			ge->GetContext()->IASetVertexBuffers(0, 1, &sub.vertexBuffer, &stride, &offset);
			ge->GetContext()->IASetIndexBuffer(sub.indexBuffer, DXGI_FORMAT_R32_UINT, 0);

			ge->GetContext()->DrawIndexed(sub.indicies.size(), 0, 0);
		}
	}
}