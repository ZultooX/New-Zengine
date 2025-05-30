#pragma once

#include <Engine/AssetManagement/Base/Asset.h>		
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Importers/VertexShaderImporter.h>
#include <Engine/AssetManagement/Exporters/VertexShaderExporter.h>

struct ID3D11InputLayout;
struct ID3D11VertexShader;
class VertexShader : public Asset
{
	BASE_ASSET(VertexShader, VertexShaderImporter, VertexShaderExporter)

public:
	const ID3D11VertexShader* GetShader() const;
	ID3D11VertexShader* GetShader();

	const ID3D11InputLayout* GetInputLayout() const;
	ID3D11InputLayout* GetInputLayout();

private:
	std::string myShaderData;
	ID3D11VertexShader* myShader = nullptr;
	ID3D11InputLayout* myInputLayout = nullptr;
};