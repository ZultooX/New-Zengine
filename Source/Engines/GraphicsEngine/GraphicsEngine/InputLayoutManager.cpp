#include "InputLayoutManager.h"
//#include "InputLayoutManager.h"
//
#include <d3d11.h>
//
#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>


namespace Zengine::Graphics
{
	std::unordered_map<const char*, ID3D11InputLayout*> InputLayoutManager::InputLayouts;


	ID3D11InputLayout* InputLayoutManager::CreateOrGet(const char* aName, const InputLayout& aLayout, const void* aShaderCode, const size_t& aSize)
	{
		if (InputLayouts.find(aName) != InputLayouts.end())
		{
			return InputLayouts[aName];
		}

		DX11GraphicsEngine* ge = ((DX11GraphicsEngine*)Engine::GetGraphicsEngine());

		ge->GetDevice()->CreateInputLayout(aLayout.Desc, aLayout.Size, aShaderCode, aSize, &InputLayouts[aName]);
		return InputLayouts[aName];
	}

	InputLayout& InputLayoutManager::GetDefaultInputLayoutDesc()
	{
		static D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
			{ "SV_POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		3, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV",	0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV",	1, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV",	2, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV",	3, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "BONES",		0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		static InputLayout layout = 
		{
			layoutDesc, (unsigned)(sizeof(layoutDesc) / sizeof(layoutDesc[0]))
		};

		return layout;
	}
}
