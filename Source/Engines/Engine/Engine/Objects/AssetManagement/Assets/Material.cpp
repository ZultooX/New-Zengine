#include "Material.h"

namespace Zengine
{
	const MaterialBufferData& Material::GetMaterialData() const { return myData; }
	MaterialBufferData& Material::GetMaterialData() { return myData; }

	void Material::SetMaterialData(const MaterialBufferData& someData)
	{
		memcpy(&myData, &someData, sizeof(MaterialBufferData));
	}

	void Material::Bind() const
	{
	}


	Color& Material::GetColor() { return myData.MB_albedoColor; }
	const Color& Material::GetColor() const { return myData.MB_albedoColor; }
	void Material::SetColor(const Color& aColor)
	{
		myData.MB_albedoColor = aColor;
		SetDirty();
	}


	float& Material::GetRoughness() { return myData.MB_roughness; }
	const float& Material::GetRoughness() const { return myData.MB_roughness; }
	void Material::SetRoughness(const float& aRoughness)
	{
		myData.MB_roughness = aRoughness;
		SetDirty();
	}


	float& Material::GetMetallic() { return myData.MB_metallic; }
	const float& Material::GetMetallic() const { return myData.MB_metallic; }
	void Material::SetMetallic(const float& aMetallic)
	{
		myData.MB_metallic = aMetallic;
		SetDirty();
	}


	float& Material::GetAoStrength() { return myData.MB_AOStrength; }
	const float& Material::GetAoStrength() const { return myData.MB_AOStrength; }
	void Material::SetAoStrength(const float& aAOStrength) { myData.MB_AOStrength = aAOStrength; }


	float& Material::GetBloomIntensity() { return myData.MB_BloomIntensity; }
	const float& Material::GetBloomIntensity() const { return myData.MB_BloomIntensity; }
	void Material::SetBloomIntensity(const float& aBloomIntensity)
	{
		myData.MB_BloomIntensity = aBloomIntensity;
		SetDirty();
	}


	float& Material::GetNormalStrength() { return myData.MB_NormalStrength; }
	const float& Material::GetNormalStrength() const { return myData.MB_NormalStrength; }
	void Material::SetNormalStrength(const float& aNormalStrength)
	{
		myData.MB_NormalStrength = aNormalStrength;
		SetDirty();
	}


	int& Material::GetTextureSetFlags() { return myData.MB_textureIsSetFlag; }
	const int& Material::GetTextureSetFlags() const { return myData.MB_textureIsSetFlag; }

	void Material::SetTextureSetFlags(const int& flags)
	{
		myData.MB_textureIsSetFlag = flags;
		SetDirty();
	}


	const AssetPointer<PixelShader>& Material::GetPixelShader() const { return myPS; }
	AssetPointer<PixelShader>& Material::GetPixelShader() { return myPS; }
	const AssetPointer<VertexShader>& Material::GetVertexShader() const { return myVS; }
	AssetPointer<VertexShader>& Material::GetVertexShader() { return myVS; }

	const std::vector<TextureData>& Material::GetTextures() const { return textures; }
	std::vector<TextureData>& Material::GetTextures() { return textures; }
}