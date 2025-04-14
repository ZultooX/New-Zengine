//#include "InputLayoutManager.h"
//
//#include <d3d11.h>
//
//#include <Engine/Engine.h>
//#include <GraphicsEngine/GraphicsEngine.h>
//
//std::vector<ID3D11InputLayout> InputLayoutManager::InputLayouts;
//
//void InputLayoutManager::Init()
//{
//	D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{ "SV_POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//
//		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "UV",	0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//
//		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "BINORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//
//		{ "BONES",		0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	};
//
//	unsigned layoutSize = sizeof(layout) / sizeof(layout[0]);
//
//	DX11GraphicsEngine* ge = ((DX11GraphicsEngine*)Engine::GetGraphicsEngine());
//	result = ge->GetDevice()->CreateInputLayout(layout, layoutSize, output.GetData().data(),
//		output.GetData().size(), &output.myInputLayout);
//
//	D3D11_INPUT_ELEMENT_DESC;
//}
