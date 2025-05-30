#pragma once

#include "ShaderResource.h"
#include <Zultools/Math/Vector2.hpp>

#include <string>

struct ID3D11DepthStencilView;

class DepthBuffer final : public ShaderResource
{
public:
	void Create(const Vector2i& aSize);
	void Clear();

public:
	ID3D11DepthStencilView* GetDSV() const { return myDSV; }

private:
	ID3D11DepthStencilView* myDSV;
};