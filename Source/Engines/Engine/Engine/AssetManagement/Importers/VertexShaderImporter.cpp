#include "VertexShaderImporter.h"

#include <Engine/AssetManagement/Assets/VertexShader.h>
#include <Engine/AssetManagement/AssetsCommon.hpp>
#include <Engine/Editor/DebugLogger.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

#include <fstream>


void VertexShaderImporter::Load(const size_t& aID, VertexShader& aOutAsset)
{
	BinaryExporter::AssetHeader header;
	std::ifstream in(ZENGINE_ASSETS_PATH "vertexshaders.bundle", std::ios::binary);

	in.read(reinterpret_cast<char*>(&header), sizeof(BinaryExporter::AssetHeader));


	BinaryExporter::AssetIndex index{};
	bool found = false;
	for (int i = 0; i < header.totalAmount; i++)
	{
		in.read(reinterpret_cast<char*>(&index), sizeof(BinaryExporter::AssetIndex));
		if (index.id == aID)
		{
			found = true;
			break;
		}
	}

	if (!found) return;

	in.seekg(index.offset);
	std::string data;
	in.read(reinterpret_cast<char*>(data.data()), index.size);



	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	HRESULT hr = ge->GetDevice()->CreateVertexShader(aOutAsset.myShaderData.data(),
		aOutAsset.myShaderData.size(), nullptr, &aOutAsset.myShader);
	in.close();

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
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

	unsigned layoutSize = sizeof(layout) / sizeof(layout[0]);

	hr = ge->GetDevice()->CreateInputLayout(layout, layoutSize, aOutAsset.myShaderData.data(),
		aOutAsset.myShaderData.size(), &aOutAsset.myInputLayout);
}

void VertexShaderImporter::Load(const char* aPath, VertexShader& aOutAsset)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	std::ifstream vsFile;
	vsFile.open(aPath, std::ios::binary);

	aOutAsset.myShaderData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	HRESULT hr = ge->GetDevice()->CreateVertexShader(aOutAsset.myShaderData.data(), 
		aOutAsset.myShaderData.size(), nullptr, &aOutAsset.myShader);
	if (FAILED(hr))
	{
		DebugLogger::LogError("Shader failed to load.");
		aOutAsset.myShader->Release();
		vsFile.close();
	}

	vsFile.close();

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
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

	unsigned layoutSize = sizeof(layout) / sizeof(layout[0]);

	hr = ge->GetDevice()->CreateInputLayout(layout, layoutSize, aOutAsset.myShaderData.data(),
		aOutAsset.myShaderData.size(), &aOutAsset.myInputLayout);
}

void VertexShaderImporter::Unload(VertexShader& aOutAsset)
{
	if(aOutAsset.myShader)aOutAsset.myShader->Release();
	if(aOutAsset.myInputLayout)aOutAsset.myInputLayout->Release();
}
