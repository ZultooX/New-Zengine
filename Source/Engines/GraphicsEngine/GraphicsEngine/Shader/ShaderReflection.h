#pragma once

#include <vector>
#include <string>
#include <d3d11.h>

struct ShaderData
{
	struct TextureData
	{
		std::string textureName;
		unsigned bindSlot;
	};

	std::vector<TextureData> textures;


	struct VariableData
	{
		std::string variableName;
		unsigned type;
		unsigned size;
		void* value;
	};

	std::vector<VariableData> variables;
};

namespace zg
{
	namespace shaders
	{
		class ShaderReflection final
		{
		public:
			static ShaderData ReflectShader(ID3DBlob* aShaderBlob);
		};
	}
}