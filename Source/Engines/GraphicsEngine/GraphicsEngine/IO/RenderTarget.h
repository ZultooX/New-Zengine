#pragma once

#include "ShaderResource.h"

#include <dxgiformat.h>
#include <Zultools/Math/Vector2.hpp>
#include <Zultools/Math/Color.h>
#include <string>

struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11Device;
struct D3D11_RENDER_TARGET_VIEW_DESC;
struct D3D11_TEXTURE2D_DESC;
class DepthBuffer;

class RenderTarget final : public ShaderResource
{
public:
	RenderTarget() = default;

public:
	void Create(const D3D11_TEXTURE2D_DESC* aTextureDesc, const D3D11_RENDER_TARGET_VIEW_DESC* aRTVDesc, const std::string& aName = "Unnamed");
	void Create(const Vector2i& aSize, const DXGI_FORMAT aFormat, const std::string& aName = "Unnamed");

	void SetAsActiveTargetOnSlot(const DepthBuffer* aDSV= nullptr);

	void Clear(const Color& aColor = {0.f, 0.f, 0.f, 0.f});

public:
	ID3D11RenderTargetView* GetRTV() const { return myRTV; }

private:
	ID3D11RenderTargetView* myRTV;
};