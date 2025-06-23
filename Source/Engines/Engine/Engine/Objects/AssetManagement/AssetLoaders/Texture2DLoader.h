#pragma once

#include <vector>
#include <Engine/Objects/AssetManagement/Assets/Texture/Texture2D.h>

namespace Zengine
{
	class Texture2DLoader
	{
	public:
		static void Load(const char* path, Texture2D& texture);

	private:
		static void Load_STBI(const char* path, Texture2D& texture);
		static void Load_DDS(const char* path, Texture2D& texture);

	private:
		static void ConvertToRGBA(const unsigned char* someData, const int& aWidth,
			const int& aHeight, std::vector<unsigned char>& outData);

		static void ConvertToGreyScale(const unsigned char* someData, const int& aWidth,
			const int& aHeight, std::vector<unsigned char>& outData);
	};
}