#include "ShaderResource.h"

#include <d3d11.h>
#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

void ShaderResource::SetAsResource(const unsigned int& aSlot, const ShaderStage& aStage)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ID3D11DeviceContext* ctx = ge->GetContext();

	switch (aStage)
	{
	case ShaderStage::Vertex:
	{
		ctx->VSSetShaderResources(aSlot, 1, GetSRVAddr());
		break;
	}
	case ShaderStage::Pixel:
	{
		ctx->PSSetShaderResources(aSlot, 1, GetSRVAddr());
		break;
	}
	case ShaderStage::Compute:
	{
		ctx->CSSetShaderResources(aSlot, 1, GetSRVAddr());
		break;
	}
	case ShaderStage::Geometry:
	{
		ctx->GSSetShaderResources(aSlot, 1, GetSRVAddr());
		break;
	}
	case ShaderStage::Hull:
	{
		ctx->HSSetShaderResources(aSlot, 1, GetSRVAddr());
		break;
	}
	case ShaderStage::Domain:
	{
		ctx->DSSetShaderResources(aSlot, 1, GetSRVAddr());
		break;
	}
	}
}
