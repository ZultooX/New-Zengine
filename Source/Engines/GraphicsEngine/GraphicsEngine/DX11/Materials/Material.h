#pragma once

#include <string>
#include <vector>
#include <GraphicsEngine/Shader/Shaders/Shader.h>
#include <Zultools/Math/Color.h>

#include <Shaders/Common/ConstantBuffers.h>


enum class BindSlot : unsigned
{
	DIFFUSE = 0, 
	NORMAL = 1, 
	MATERIAL = 2, 
};

struct TextureData
{
	std::string textureName;
	std::string texturePath;
	unsigned bindSlot;
};

class Material
{
public:
	Material(const std::string& aDiffusePath, const std::string& aNormalPath, const std::string& aMaterialPath, const std::string& aPixelShader, const std::string& aVertexShader);
	Material(const std::string& aPath);

	void CreateMaterial();

	void AddTexture(const std::string& aTextureName, const std::string& aTexturePath, const unsigned& aBindSlot);
	const std::vector<TextureData>& GetTextures() const;

	inline const Zengine::Graphics::Shader& GetShader() const { return myShader; }
	inline Zengine::Graphics::Shader& GetShader() { return myShader; }

	inline void SetColor(const Color& aColor) { myMaterialData.MB_albedoColor = aColor; }
	inline Color& GetColor() { return myMaterialData.MB_albedoColor; }
	inline const Color& GetColor() const { return myMaterialData.MB_albedoColor; }

	void Bind() const;

	const MaterialBufferData& GetMaterialData() const;

public:
	void Save();
	void Save(const std::string& aPath);

private:
	void Load();

private:
	std::string myPath;

	std::vector<TextureData> myTextures;

	Zengine::Graphics::Shader myShader = {};
	MaterialBufferData myMaterialData;
};