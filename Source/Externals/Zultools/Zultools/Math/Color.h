#pragma once

class Color
{
public:
	float r, g, b, a;

	const float* GetPtr() const { return &r; }
};