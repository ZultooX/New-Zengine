#include "VertexShaderLoader.h"

#include <unordered_map>
#include <fstream>
#include <d3d11.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>

namespace Zengine
{
	enum class Importers
	{
		Uncompiled, Compiled
	};

	void VertexShaderLoader::Load(const char* path, VertexShader& shader)
	{
		static std::unordered_map<const char*, Importers> supportedFiles = {
			{ ".cso" , Importers::Compiled },
			{ ".hlsl" , Importers::Uncompiled },
		};

		Importers importer = supportedFiles[path];

		switch (importer)
		{
		case Importers::Compiled: LoadCompiledShader(path, shader); break;
		case Importers::Uncompiled: LoadUncompiledShader(path, shader); break;
		}
	}

	void VertexShaderLoader::LoadCompiledShader(const char* path, VertexShader& shader)
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		std::ifstream vsFile;
		vsFile.open(path, std::ios::binary);

		shader.SetShaderData({ std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() });
		HRESULT hr = ge->GetDevice()->CreateVertexShader(shader.GetShaderData().data(),
			shader.GetShaderData().size(), nullptr, shader.GetShaderAddr());
		if (FAILED(hr))
		{
			shader.GetShader()->Release();
			vsFile.close();
		}

		vsFile.close();

		CreateInputLayout(path, shader);
	}

	void VertexShaderLoader::LoadUncompiledShader(const char* path, VertexShader& shader)
	{

	}

	void VertexShaderLoader::CreateInputLayout(const char* path, VertexShader& shader)
	{
		DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "SV_POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		3, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "UV",			0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV",			1, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV",			2, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV",			3, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			{ "BONES",		0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		unsigned layoutSize = sizeof(layout) / sizeof(layout[0]);

		ge->GetDevice()->CreateInputLayout(layout, layoutSize, shader.GetShaderData().data(),
			shader.GetShaderData().size(), shader.GetInputLayoutAddr());
	}
}