#pragma once

#include <string>

enum class ShaderStage
{
	Vertex,
	Pixel,
	Compute,
	Geometry,
	Hull,
	Domain
};

struct ID3D11ShaderResourceView;
struct ID3D11Texture2D;

class ShaderResource
{
public:
	void SetAsResourceOnSlot(unsigned int aSlot, ShaderStage aStage = ShaderStage::Pixel);

	void SetName(const std::string& aName);

	ID3D11ShaderResourceView* GetSRV() const { return mySRV; }
	ID3D11ShaderResourceView** GetSRVAddress() { return &mySRV; }

	ID3D11Texture2D* GetTexture() const { return myTexture; }
	ID3D11Texture2D** GetTextureAddress() { return &myTexture; }

protected:
	ID3D11ShaderResourceView* mySRV = nullptr;
	ID3D11Texture2D* myTexture;
	std::string myName;
};