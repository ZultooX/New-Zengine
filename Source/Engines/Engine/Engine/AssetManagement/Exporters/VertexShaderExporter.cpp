#include "VertexShaderExporter.h"

#include <Engine/AssetManagement/AssetsCommon.hpp>
#include <Engine/AssetManagement/Assets/VertexShader.h>

#include <filesystem>
#include <fstream>

void VertexShaderExporter::ExportToBinaryFile(const char* aOutDst, const VertexShader& aVertexShader)
{
}

void VertexShaderExporter::ExportAllToBinaryFile(const char* aOutDst)
{
	std::vector<BinaryExporter::ShaderData> myBinaryData;
	std::vector<BinaryExporter::AssetIndex> myIndex;

	for (const auto& entry : std::filesystem::directory_iterator(ZENGINE_SHADERS_PATH "Vertex"))
	{
		BinaryExporter::ShaderData data;

		std::ifstream in(entry.path(), std::ios::binary | std::ios::ate);
		if (in) 
		{
			std::streamsize size = in.tellg();
			in.seekg(0, std::ios::beg);

			data.data.resize(size);
			if (size > 0) 
			{
				in.read(&data.data[0], size);
			}
		}

		BinaryExporter::AssetIndex index;
		index.id = std::hash<std::string>{}(entry.path().string());
		index.size = (int)data.data.size();

		myBinaryData.emplace_back(std::move(data));
		myIndex.emplace_back(std::move(index));

		in.close();
	}

	for (int i = 0; i < (int)myBinaryData.size(); i++)
	{
		if (i == 0)
		{
			myIndex[i].offset = sizeof(BinaryExporter::AssetHeader) + sizeof(BinaryExporter::AssetIndex) * myIndex.size();
		}
		else
		{
			myIndex[i].offset = myIndex[i - 1].offset + myIndex[i - 1].size;
		}
	}

	std::ofstream out(aOutDst, std::ios::binary);
	if (!out.is_open()) return;

	BinaryExporter::AssetHeader header;
	header.totalAmount = static_cast<int>(myBinaryData.size());
	out.write(reinterpret_cast<const char*>(&header), sizeof(header));

	for (const BinaryExporter::AssetIndex& idx : myIndex)
	{
		out.write(reinterpret_cast<const char*>(&idx), sizeof(BinaryExporter::AssetIndex));
	}

	for (const BinaryExporter::ShaderData& data : myBinaryData)
	{
		out.write(data.data.data(), data.data.size());
	}

	out.close();
}
