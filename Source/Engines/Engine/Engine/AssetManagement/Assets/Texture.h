#pragma once

#include <Engine/AssetManagement/Base/Asset.h>		
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Importers/TextureImporter.h>
#include <Engine/AssetManagement/Exporters/TextureExporter.h>

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;
class Texture : public Asset
{
	BASE_ASSET(Texture, TextureImporter, TextureExporter)

public:
	const ID3D11Texture2D* GetTexture() const { return myTexture;};
	ID3D11Texture2D* GetTexture() { return myTexture; };

	ID3D11Texture2D* const* GetTextureAddress() const { return &myTexture; };
	ID3D11Texture2D** GetTextureAddress() { return &myTexture; };


	const ID3D11ShaderResourceView* GetShaderResource() const { return myResourceView; };
	ID3D11ShaderResourceView* GetShaderResource() { return myResourceView; };

	ID3D11ShaderResourceView* const* GetShaderResourceAddress() const { return &myResourceView; };
	ID3D11ShaderResourceView** GetShaderResourceAddress() { return &myResourceView; };

private:
	ID3D11Texture2D* myTexture = nullptr;
	ID3D11ShaderResourceView* myResourceView = nullptr;
};