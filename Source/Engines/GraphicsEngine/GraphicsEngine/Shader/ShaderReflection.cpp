#include "ShaderReflection.h"

#include <d3dcompiler.h>

#include <d3d11.h>

namespace Zengine::Graphics
{
	ShaderData ShaderReflection::ReflectShader(ID3DBlob* aShaderBlob)
	{
		ID3D11ShaderReflection* reflection;
		D3DReflect(aShaderBlob->GetBufferPointer(), aShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection);

		D3D11_SHADER_DESC shaderDesc;
		reflection->GetDesc(&shaderDesc);

		if (shaderDesc.BoundResources == 0) return ShaderData();

		ShaderData data;

		unsigned publicContainerSlot = -1;
		for (unsigned i = 0; i < shaderDesc.BoundResources; ++i)
		{
			D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
			reflection->GetResourceBindingDesc(i, &resourceDesc);

			if (resourceDesc.Type == D3D_SIT_CBUFFER && resourceDesc.Name == "PublicContainer")
			{
				publicContainerSlot = resourceDesc.BindPoint;
			}
			else if (resourceDesc.Type == D3D_SIT_TEXTURE)
			{
				data.textures.push_back({ resourceDesc.Name, resourceDesc.BindPoint });
			}
		}

		if (publicContainerSlot == -1) return ShaderData();

		ID3D11ShaderReflectionConstantBuffer* cbuff = reflection->GetConstantBufferByIndex(publicContainerSlot);
		D3D11_SHADER_BUFFER_DESC cbDesc;
		cbuff->GetDesc(&cbDesc);

		for (unsigned i = 0; i < cbDesc.Variables; ++i)
		{
			ID3D11ShaderReflectionVariable* variable = cbuff->GetVariableByIndex(i);
			D3D11_SHADER_VARIABLE_DESC varDesc;
			variable->GetDesc(&varDesc);

			ID3D11ShaderReflectionType* type = variable->GetType();
			D3D11_SHADER_TYPE_DESC typeDesc;
			type->GetDesc(&typeDesc);

			{
				ShaderData::VariableData varData;

				if (typeDesc.Type == D3D_SVT_BOOL)
				{
					bool* defaultValue = reinterpret_cast<bool*>(varDesc.DefaultValue);
					varData.value = malloc(sizeof(bool));
					memcpy(varData.value, defaultValue, varDesc.Size);
				}
				else
				{
					varData.value = malloc(varDesc.Size);
					memcpy(varData.value, varDesc.DefaultValue, varDesc.Size);
				}

				varData.variableName = varDesc.Name;
				varData.type = typeDesc.Type;
				varData.size = varDesc.Size;

				data.variables.emplace_back(varData);
			}
		}

		return data;
	}
}