#include "PixelShaderImporter.h"

#include <Engine/AssetManagement/Assets/PixelShader.h>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>
#include <Engine/AssetManagement/AssetsCommon.hpp>

#include <fstream>

void PixelShaderImporter::Load(const size_t& aID, PixelShader& aOutAsset)
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
	HRESULT result = ge->GetDevice()->CreatePixelShader(data.data(), data.size(), nullptr, &aOutAsset.myShader);
}

void PixelShaderImporter::Load(const char* aPath, PixelShader& aOutAsset)
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();

	std::ifstream psFile;
	psFile.open(aPath, std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
	HRESULT result = ge->GetDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &aOutAsset.myShader);

	psFile.close();
}

void PixelShaderImporter::Unload(PixelShader& aOutAsset)
{
	aOutAsset.myShader->Release();
}
