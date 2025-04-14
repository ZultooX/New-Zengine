#pragma once

#include <string>

#include <unordered_map>
#include <vector>

template<typename T>
class AbstractAssetManager
{
public:
	virtual void Init() { __noop; };

	virtual T* Get(const std::string& aAssetPath);
	virtual T* Load(const std::string& aAssetPath) = 0;

protected:
	std::unordered_map<std::string, unsigned> myPathToIdx;
	std::vector<T*> myAssets;
};

template<typename T>
inline T* AbstractAssetManager<T>::Get(const std::string& aAssetPath)
{
	auto it = myPathToIdx.find(aAssetPath);
	if (it != myPathToIdx.end())
	{
		return myAssets[it->second];
	}

	return Load(aAssetPath);
}
