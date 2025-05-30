#include "PixelShader.h"

const ID3D11PixelShader* PixelShader::GetShader() const { return myShader; }
ID3D11PixelShader* PixelShader::GetShader() { return myShader; }
