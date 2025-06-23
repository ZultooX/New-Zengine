#include "Texture.h"

#include <d3d11.h>
#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>


namespace Zengine
{
	Zengine::Texture::Texture() : Asset() {  }
	Texture::Texture(const size_t& _id) : Asset(_id) {	}

	void Texture::BindAsResource(const unsigned& slot, const int& stage)
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		if (stage & PipelineStage::VertexShader)
			ge->GetContext()->VSSetShaderResources(slot, 1, &srv);

		if (stage & PipelineStage::PixelShader)
			ge->GetContext()->PSSetShaderResources(slot, 1, &srv);

		if (stage & PipelineStage::HullShader)
			ge->GetContext()->HSSetShaderResources(slot, 1, &srv);

		if (stage & PipelineStage::ComputeShader)
			ge->GetContext()->CSSetShaderResources(slot, 1, &srv);
	}

	const ID3D11ShaderResourceView* Texture::GetSRV() const { return srv; }
	ID3D11ShaderResourceView* Texture::GetSRV() { return srv; }
	ID3D11ShaderResourceView** Texture::GetSRVAddr() { return &srv; }
}