#include "MaterialManager.h"


Material* MaterialManager::Load(const std::string& aMaterialPath)
{
    myPathToIdx[aMaterialPath] = myAssets.size();

    myAssets.emplace_back(new Material(aMaterialPath.c_str()));

    return myAssets.back();
}

