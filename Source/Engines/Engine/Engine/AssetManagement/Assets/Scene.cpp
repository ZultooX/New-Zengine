#include "VertexShader.h"

const ID3D11VertexShader* VertexShader::GetShader() const { return myShader; }
ID3D11VertexShader* VertexShader::GetShader() { return myShader; }

const ID3D11InputLayout* VertexShader::GetInputLayout() const { return myInputLayout; }
ID3D11InputLayout* VertexShader::GetInputLayout() { return myInputLayout; }