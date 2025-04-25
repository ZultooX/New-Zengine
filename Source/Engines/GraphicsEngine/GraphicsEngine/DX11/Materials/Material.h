#pragma once

#include <string>
#include <vector>
#include <GraphicsEngine/Shader/Shaders/Shader.h>

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


	void AddTexture(const std::string& aTextureName, const std::string& aTexturePath, const unsigned& aBindSlot);
	const std::vector<TextureData>& GetTexture();

	inline const Zengine::Graphics::Shader& GetShader() { return myShader; }

public:
	void Save();
	void Save(const std::string& aPath);

private:
	void Load();

private:
	std::string myPath;

	std::vector<TextureData> myTextures;

	Zengine::Graphics::Shader myShader = {};
};