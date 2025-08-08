#pragma once

#include <Engine/Objects/AssetManagement/Base/Asset.h>
#include <Engine/Objects/Base/AssetPointer.hpp>
#include <Engine/Objects/AssetManagement/Assets/Texture.h>
#include <Engine/Objects/AssetManagement/Assets/Shaders/PixelShader.h>
#include <Engine/Objects/AssetManagement/Assets/Shaders/VertexShader.h>
#include <Shaders/Common/ConstantBuffers.h>

#include <string>

namespace Zengine
{
	struct TextureData
	{
		std::string name;
		AssetPointer<Texture> texture;
		unsigned bindPoint;
	};

    class Material : public virtual Asset
    {
		friend class MaterialLoader;

    public:
        Material();
        Material(const size_t& _id);
        virtual ~Material() = default;

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
		void SetTextureSetFlags(const int& flags);

		const AssetPointer<PixelShader>& GetPixelShader() const;
		AssetPointer<PixelShader>& GetPixelShader();
		const AssetPointer<VertexShader>& GetVertexShader() const;
		AssetPointer<VertexShader>& GetVertexShader();

		const std::vector<TextureData>& GetTextures() const;
		std::vector<TextureData>& GetTextures();

	private:
		std::vector<TextureData> textures;

		MaterialBufferData myData;

		AssetPointer<PixelShader> myPS;
		AssetPointer<VertexShader> myVS;
    };
}