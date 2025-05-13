#include "Material.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

#include <GraphicsEngine/GraphicsEngine.h>
#include <Engine/Engine.h>
#include <GraphicsEngine/DX11/Buffers/BufferManager.h>
#include <Engine/Utilities/MainSingleton.h>

namespace Json
{
	namespace Color
	{
		inline constexpr const char* Key = "color";
		inline constexpr const char* R = "r";
		inline constexpr const char* G = "g";
		inline constexpr const char* B = "b";
		inline constexpr const char* A = "a";

		inline constexpr float DefaultR = 1.0f;
		inline constexpr float DefaultG = 1.0f;
		inline constexpr float DefaultB = 1.0f;
		inline constexpr float DefaultA = 1.0f;
	}

	inline constexpr const char* TexturesKey = "Textures";

	inline constexpr const char* VertexShaderKey = "sh_vertex";
	inline constexpr const char* VertexShaderDefault = ZENGINE_SHADERS_PATH"VS_Default.cso";

	inline constexpr const char* PixelShaderKey = "sh_pixel";
	inline constexpr const char* PixelShaderDefault = ZENGINE_SHADERS_PATH"PS_Default.cso";

}

Material::Material(const std::string& aPath) : myPath(aPath)
{
	if (std::filesystem::exists(aPath)) Load();
	else CreateMaterial();
}

void Material::CreateMaterial()
{
	std::ofstream file(myPath);
	file.close();

	Save();
}

void Material::AddTexture(const std::string& aTextureName, const std::string& aTexturePath, const unsigned& aBindSlot)
{
	if (aBindSlot == (unsigned)BindSlot::NORMAL)
	{
		Zengine::Utilities::BitMask<> mask;
		mask.SetBit(10, true);
		myMaterialData.MB_TextureSetBitSet = mask.GetMask();
	}

	myTextures.push_back({ aTextureName, aTexturePath, aBindSlot });
}

const std::vector<TextureData>& Material::GetTextures() const
{
	return myTextures;
}

void Material::Load()
{
	using namespace nlohmann;

	std::ifstream file(myPath);
	json jsonFile;
	jsonFile << file;

	Zengine::Util::BitMask<> bit;
	for (json& element : jsonFile[Json::TexturesKey])
	{
		myTextures.push_back(TextureData());
		myTextures.back().textureName = element[0];
		myTextures.back().texturePath = element[1];
		myTextures.back().bindSlot = element[2];

		bit.SetBit(myTextures.back().bindSlot, true);
		myMaterialData.MB_TextureSetBitSet = bit.GetMask();
	}

	myShader.SetVertexShader(jsonFile.value(Json::VertexShaderKey, Json::VertexShaderDefault).c_str());
	myShader.SetPixelShader(jsonFile.value(Json::PixelShaderKey, Json::PixelShaderDefault).c_str());

	if (jsonFile.contains(Json::Color::Key))
	{
		const json& color = jsonFile[Json::Color::Key];

		myMaterialData.MB_albedoColor.r = color.value(Json::Color::R, Json::Color::DefaultR);
		myMaterialData.MB_albedoColor.g = color.value(Json::Color::G, Json::Color::DefaultG);
		myMaterialData.MB_albedoColor.b = color.value(Json::Color::B, Json::Color::DefaultB);
		myMaterialData.MB_albedoColor.a = color.value(Json::Color::A, Json::Color::DefaultA);
	}
}

void Material::Bind() const
{
	MainSingleton::GetInstance<Zengine::Buffers::BufferManager>().UpdateMaterialBuffer(myMaterialData);
}

const MaterialBufferData& Material::GetMaterialData() const
{
	return myMaterialData;
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
		json[Json::TexturesKey].push_back({ texture.textureName, texture.texturePath, texture.bindSlot });
	}

	if (myShader.GetVertexShader())
	{
		json[Json::VertexShaderKey] = myShader.GetVertexShader()->GetPath();
	}
	else
	{
		json[Json::VertexShaderKey] = Json::VertexShaderDefault;
	}

	if (myShader.GetPixelShader())
	{
		json[Json::PixelShaderKey] = myShader.GetPixelShader()->GetPath();
	}
	else
	{
		json[Json::PixelShaderKey] = Json::PixelShaderDefault;
	}

	json[Json::Color::Key] =
	{
		{Json::Color::R, myMaterialData.MB_albedoColor.r},
		{Json::Color::G, myMaterialData.MB_albedoColor.g},
		{Json::Color::B, myMaterialData.MB_albedoColor.b},
		{Json::Color::A, myMaterialData.MB_albedoColor.a},
	};

	std::fstream file(aPath);
	if (!file.is_open()) return;

	file << json.dump(4);

	file.close();
}


