#pragma once

template<typename T>
class AssetImporter {
public:
	virtual void Init() { __noop; }

	virtual void Load(const char* aPath, void* aOutAsset) { __noop; }
};