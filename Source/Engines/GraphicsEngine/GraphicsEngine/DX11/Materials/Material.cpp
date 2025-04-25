#include "Material.h"

#include <nlohmann/json.hpp>
#include <fstream>


Material::Material(const std::string& aPath) : myPath(aPath)
{
	Load();
}

void Material::AddTexture(const std::string& aTextureName, const std::string& aTexturePath, const unsigned& aBindSlot)
{
	myTextures.push_back({ aTextureName, aTextureName, aBindSlot });
}

const std::vector<TextureData>& Material::GetTexture()
{
	return myTextures;
}

void Material::Load()
{
}

void Material::Save()
{
	Save(myPath);
}

void Material::Save(const std::string& aPath)
{
	myPath = aPath;

	using namespace nlohmann;

	ordered_json  json;
	
	for (const TextureData& texture : myTextures)
	{
		json[texture.textureName] = { texture.texturePath, texture.bindSlot };
	}

	json["sh_vertex"] = myShader.GetVertexShader()->GetPath();
	json["sh_pixel"] = myShader.GetPixelShader()->GetPath();

	std::fstream file(aPath);
	if (!file.is_open()) return;

	file << json.dump(4);
}


