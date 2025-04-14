#include "Shader.h"

#include <d3d11.h>

#include <Engine/Engine.h>
#include <GraphicsEngine/GraphicsEngine.h>

void zg::shaders::Shader::Bind()
{
	DX11GraphicsEngine* ge = (DX11GraphicsEngine*)Engine::GetGraphicsEngine();
	ge->GetContext()->PSSetShader(myPixelShader->GetShader(), nullptr, 0);
	ge->GetContext()->VSSetShader(myVertexShader->GetShader(), nullptr, 0);
}
