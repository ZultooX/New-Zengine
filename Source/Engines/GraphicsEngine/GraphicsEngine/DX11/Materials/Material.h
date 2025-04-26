#pragma once

#include <string>
#include <vector>
#include <GraphicsEngine/Shader/Shaders/Shader.h>
#include <Zultools/Math/Color.h>
#include <GraphicsEngine/DX11/Buffers/BufferDatas.h>

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

	inline void SetColor(const Color& aColor) { myMaterialData.Color = aColor; }
	inline Color& GetColor() { return myMaterialData.Color; }
	inline const Color& GetColor() const { return myMaterialData.Color; }

	void Bind() const;

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