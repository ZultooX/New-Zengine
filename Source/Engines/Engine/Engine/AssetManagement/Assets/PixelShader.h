#pragma once

#include <Engine/AssetManagement/Base/Asset.h>		
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Importers/PixelShaderImporter.h>
#include <Engine/AssetManagement/Exporters/PixelShaderExporter.h>

struct ID3D11PixelShader;
class PixelShader : public Asset
{
	BASE_ASSET(PixelShader, PixelShaderImporter, PixelShaderExporter)

public:
	const ID3D11PixelShader* GetShader() const;
	ID3D11PixelShader* GetShader();

private:
	std::string myShaderData;
	ID3D11PixelShader* myShader = nullptr;
};