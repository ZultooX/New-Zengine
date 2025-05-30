#include "MeshExporter.h"

#include <Engine/AssetManagement/AssetsCommon.hpp>
#include <Engine/AssetManagement/Assets/Mesh.h>

#include <filesystem>
#include <fstream>

void MeshExporter::ExportToBinaryFile(const char* aOutDst, const Mesh& aMesh)
{
}

void MeshExporter::ExportAllToBinaryFile(const char* aOutDst)
{
	std::vector<BinaryExporter::MeshData> myBinaryData;
	std::vector<BinaryExporter::AssetIndex> myIndex;

	for (const auto& entry : std::filesystem::directory_iterator(ZENGINE_MODELS_PATH))
	{
		Mesh mesh = Mesh(entry.path().string().c_str());

		for (const SubMesh& sub : mesh.GetSubmeshes())
		{
			BinaryExporter::MeshData data;
			data.verts.insert(data.verts.begin(), sub.verticies.begin(), sub.verticies.end());
			data.indicies.insert(data.indicies.begin(), sub.indicies.begin(), sub.indicies.end());


			BinaryExporter::AssetIndex index;
			index.id = std::hash<std::string>{}(sub.meshName);
			index.size = data.verts.size() * sizeof(Vertex) + data.indicies.size() * sizeof(unsigned) + sizeof(int) * 2;

			myBinaryData.emplace_back(std::move(data));
			myIndex.emplace_back(std::move(index));
		}
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

	for (const BinaryExporter::MeshData& data : myBinaryData)
	{
		int vertSize = (int)data.verts.size();
		int indiciesSize = (int)data.indicies.size();
		out.write(reinterpret_cast<const char*>(&vertSize), sizeof(int));
		out.write(reinterpret_cast<const char*>(&indiciesSize), sizeof(int));

		for (const Vertex& vert : data.verts)
		{
			out.write(reinterpret_cast<const char*>(&vert), sizeof(Vertex));
		}

		for (const unsigned& indicies : data.indicies)
		{
			out.write(reinterpret_cast<const char*>(&indicies), sizeof(unsigned));
		}
	}

	out.close();
}
