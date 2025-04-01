#pragma once

#include <string>

#include <d3d11.h>



class IShader 
{
public:
	ID3DBlob* CompileShader(const WCHAR* aPath, const LPCSTR aShaderModel, const std::string& aEntryPoint);

protected:
	virtual void Compile() = 0;

protected:
	ID3D11DeviceChild* myShader;
	std::string myShaderPath;
};