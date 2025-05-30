#pragma once

class Material;
class MaterialImporter
{
public:
	static void Load(const size_t& aID, Material& aOutAsset);
	static void Load(const char* aPath, Material& aOutAsset);
	static void Unload(Material& aOutAsset);
};

