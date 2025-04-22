#include "PixelShaderManager.h"

Zengine::Graphics::PixelShader* PixelShaderManager::Load(const std::string& aShaderPath)
{
    myPathToIdx[aShaderPath] = myAssets.size();

    myAssets.emplace_back(new Zengine::Graphics::PixelShader(aShaderPath.c_str()));

    return myAssets.back();
}
