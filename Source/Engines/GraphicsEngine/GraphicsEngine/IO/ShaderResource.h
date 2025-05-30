#pragma once

#include <Zultools/Math/Vector2.hpp>

enum class ShaderStage
{
	Vertex,
	Pixel,
	Compute,
	Geometry,
	Hull,
	Domain
};

struct D3D11_SHADER_RESOURCE_VIEW_DESC;
struct ID3D11ShaderResourceView;
struct D3D11_TEXTURE2D_DESC;
struct ID3D11Texture2D;

class ShaderResource 
{
public:
	~ShaderResource() = default;
	ShaderResource() = default;

public:
	virtual void SetAsResource(const unsigned int& aSlot, const ShaderStage& aStage);

#pragma region [Getters SRV]
	inline ID3D11ShaderResourceView* GetSrv() { return mySRV; }
	inline const ID3D11ShaderResourceView* GetSrv() const { return mySRV; }

	inline ID3D11ShaderResourceView** GetSRVAddr() { return &mySRV; }
#pragma endregion

#pragma region [Getters TEXTURE]
	inline ID3D11Texture2D* GetTexture() { return myTexture; }
	inline const ID3D11Texture2D* GetTexture() const { return myTexture; }

	inline ID3D11Texture2D** GetTextureAddr() { return &myTexture; }
#pragma endregion

protected:
	ID3D11ShaderResourceView* mySRV = nullptr;
	ID3D11Texture2D* myTexture = nullptr;
};
