#pragma once

#include <vector>
#include <unordered_map>

struct ID3D11InputLayout;
struct D3D11_INPUT_ELEMENT_DESC;

struct InputLayout
{
	D3D11_INPUT_ELEMENT_DESC* Desc = nullptr;
	unsigned Size = 0;
};

namespace Zengine::Graphics
{
	class InputLayoutManager final
	{
	public:
		static ID3D11InputLayout* CreateOrGet(const char* aName, const InputLayout& aLayout, const void* aShaderCode, const size_t& aSize);
		static InputLayout& GetDefaultInputLayoutDesc();

	private:
		static std::unordered_map<const char*, ID3D11InputLayout*> InputLayouts;
	};
}

namespace zg = Zengine::Graphics;