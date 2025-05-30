#pragma once

class VertexShader;
class VertexShaderImporter final
{
public:
	static void Load(const size_t&  aID, VertexShader& aOutAsset);
	static void Load(const char* aPath, VertexShader& aOutAsset);
	static void Unload(VertexShader& aOutAsset);
};

