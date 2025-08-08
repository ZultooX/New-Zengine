#pragma once

#include <GraphicsEngine/GraphicsStructs.h>
#include <Shaders/Common/ConstantBuffers.h>
#include <vector>

namespace BinaryExporter
{
	struct AssetHeader
	{
		int totalAmount;
	};

	struct AssetIndex
	{
		size_t id;
		int offset;
		int size;
	};

	struct TextureIndex : public AssetIndex
	{
		int channels; 
		int width; 
		int height; 
	};

	struct MeshIndex : public AssetIndex {
		std::string name;
		int meshCount;
	};

	struct MeshData {
		int vertCount;
		std::vector<Vertex> verts;
		int indiCount;
		std::vector<unsigned> indicies;
	};

	struct ShaderData
	{
		std::string data;
	};

	struct MaterialData
	{
		struct Texture {
			int bindPoint;
			size_t textureID;
		};

		MaterialBufferData data;
		std::vector<Texture> textures;
		size_t pixelShaderID;
		size_t vertexShaderID;
	};
}