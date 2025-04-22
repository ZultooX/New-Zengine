#include "VertexShaderManager.h"

Zengine::Graphics::VertexShader* VertexShaderManager::Load(const std::string& aShaderPath)
{
    myPathToIdx[aShaderPath] = myAssets.size();

    myAssets.emplace_back(new Zengine::Graphics::VertexShader(aShaderPath.c_str()));

    return myAssets.back();
}
