#include "Shader.h"

#include <d3dcompiler.h>
#include <fstream>

class ShaderIncludeHandler : public ID3DInclude
{
public:
    STDMETHOD(Open)(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override
    {
        IncludeType;
        pParentData;

        std::string filePath = "";
        std::string shaderIncludesIncludeString(std::string(pFileName).substr(0, 6));

        if (shaderIncludesIncludeString == "Common")
        {
            filePath = "../Source/Engines/GraphicsEngine/GraphicsEngine/Shaders/" + std::string(pFileName);
        }
        else
        {
            filePath = "../Source/Engines/GraphicsEngine/GraphicsEngine/Shaders/Common/" + std::string(pFileName);
        }

        std::ifstream fileStream(filePath, std::ios::binary);

        if (!fileStream.is_open())
            return E_FAIL;

        fileStream.seekg(0, std::ios::end);
        size_t size = fileStream.tellg();
        fileStream.seekg(0, std::ios::beg);

        char* buffer = new char[size];
        fileStream.read(buffer, size);
        fileStream.close();

        *ppData = buffer;
        *pBytes = static_cast<UINT>(size);

        return S_OK;
    }
    STDMETHOD(Close)(LPCVOID pData) override
    {
        delete[] static_cast<const char*>(pData);
        return S_OK;
    }
};











ID3DBlob* IShader::CompileShader(const WCHAR* aPath, const LPCSTR aShaderModel, const std::string& aEntryPoint)
{
    HRESULT hr = S_OK;
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
    dwShaderFlags |= D3DCOMPILE_DEBUG;
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* outBlob;

    ID3DBlob* pErrorBlob = nullptr;
    ShaderIncludeHandler includeHandler;

    hr = D3DCompileFromFile(aPath, nullptr, &includeHandler, aEntryPoint.c_str(), aShaderModel,
        dwShaderFlags, 0, &outBlob, &pErrorBlob);

    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            pErrorBlob->Release();
        }
    }

    if (pErrorBlob) pErrorBlob->Release();

    return outBlob;
}