#pragma once

class PixelShader;
class PixelShaderImporter
{
public:
	static void Load(const size_t& aID, PixelShader& aOutAsset);
	static void Load(const char* aPath, PixelShader& aOutAsset);
	static void Unload(PixelShader& aOutAsset);
};

