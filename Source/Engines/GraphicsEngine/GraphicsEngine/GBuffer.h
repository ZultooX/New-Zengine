#pragma once

#include <Zultools\Math\Vector2.hpp>
//#include "Texture\DepthBuffer.h"

#include <array>
#include <memory>
#include <wrl\client.h>

using Microsoft::WRL::ComPtr;


struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;
struct D3D11_VIEWPORT;
class DepthBuffer;

class GBuffer
{
public:
	enum class GBufferTexture {
		WorldPosition,
		Albedo,
		Normal,
		Material,
		AmbientOcclusionAndCustom,
		Count,
	};

	std::array<ComPtr<ID3D11Texture2D>, (int)GBufferTexture::Count> myTextures;
	std::array<ComPtr<ID3D11RenderTargetView>, (int)GBufferTexture::Count> myRTVs;
	std::array<ComPtr<ID3D11ShaderResourceView>, (int)GBufferTexture::Count> mySRVs;
	std::shared_ptr<const D3D11_VIEWPORT> myViewport;

public:
	GBuffer() = default;
	~GBuffer() = default;

	static GBuffer Create(Vector2i aSize);
	void ClearTextures();
	void SetAsActiveTarget(DepthBuffer* aDepth = nullptr);
	void SetAsTarget(GBufferTexture atexture);
	void SetAsResourceOnSlot(GBufferTexture atexture, unsigned aSlot);
	void SetAllAsResources(unsigned aSlot);

	void Unbind();
	void Cleanup();

	ComPtr<ID3D11ShaderResourceView> GetSRV(GBufferTexture aTexture);
};

