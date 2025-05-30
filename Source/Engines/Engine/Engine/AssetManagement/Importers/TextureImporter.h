#pragma once

#include <Engine/Editor/DebugLogger.h>

class Texture;
class TextureImporter final
{
public:
	static void Load(const size_t& aID, Texture& aOutAsset);
	static void Load(const char* aPath, Texture& aOutAsset);
	static void Unload(Texture& aOutAsset);

private:
	static void Load_STBI(const char* aPath, Texture& aOutAsset);
	static void Load_DDS(const char* aPath, Texture& aOutAsset);
	static void Load_Binary(const size_t& anID, Texture& aOutAsset)
	{
		DebugLogger::LogWarning(__FILE__ " | Method not implemented.");
	};

private:
	static void ConvertToRGBA(const unsigned char* someData, const int& aWidth,
		const int& aHeight, std::vector<unsigned char>& aOutDst);

	static void ConvertToGreyScale(const unsigned char* someData, const int& aWidth,
		const int& aHeight, std::vector<unsigned char>& aOutDst);
};

