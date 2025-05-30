#pragma once

#include <Engine/AssetManagement/Base/Asset.h>		
#include <Engine/AssetManagement/AssetManager.h>
#include <Engine/AssetManagement/Importers/MaterialImporter.h>
#include <Engine/AssetManagement/Exporters/MaterialExporter.h>


#include <Shaders/Common/ConstantBuffers.h>

#include <Engine/AssetManagement/Assets/PixelShader.h>		
#include <Engine/AssetManagement/Assets/VertexShader.h>		
#include <Engine/AssetManagement/Assets/Texture.h>		

class Texture;
struct TextureData
{
	AssetPointer<Texture> texture;
	unsigned bindPoint;

	// Debug value only, not used in the build.
	std::string name;
};

class PixelShader;
class VertexShader;
class Material : public Asset
{
	BASE_ASSET(Material, MaterialImporter, MaterialExporter)

public:
	const MaterialBufferData& GetMaterialData()const;
	MaterialBufferData& GetMaterialData();

	void SetMaterialData(const MaterialBufferData& someData);

	void Bind() const;

public:
	Color& GetColor();
	const Color& GetColor() const;
	void SetColor(const Color& aColor);

	float& GetRoughness();
	const float& GetRoughness() const;
	void SetRoughness(const float& aRoughness);

	float& GetMetallic();
	const float& GetMetallic() const;
	void SetMetallic(const float& aMetallic);

	float& GetAoStrength();
	const float& GetAoStrength() const;
	void SetAoStrength(const float& aAOStrength);

	float& GetBloomIntensity();
	const float& GetBloomIntensity() const;
	void SetBloomIntensity(const float& aBloomIntensity);

	float& GetNormalStrength();
	const float& GetNormalStrength() const;
	void SetNormalStrength(const float& aNormalStrength);

	int& GetTextureSetFlags();
	const int& GetTextureSetFlags() const;

	const AssetPointer<PixelShader>& GetPixelShader() const;
	AssetPointer<PixelShader>& GetPixelShader();
	const AssetPointer<VertexShader>& GetVertexShader() const;
	AssetPointer<VertexShader>& GetVertexShader();

	const std::vector<TextureData>& GetTextures() const;
	std::vector<TextureData>& GetTextures();

private:
	MaterialBufferData myData;

	AssetPointer<PixelShader> myPS;
	AssetPointer<VertexShader> myVS;

	std::vector<TextureData> myTextures;
};