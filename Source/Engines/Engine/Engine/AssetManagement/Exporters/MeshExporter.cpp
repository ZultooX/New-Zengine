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
	std::vector<BinaryExporter::MeshIndex> myIndex;

	std::vector<MeshData> meshData;
	MeshImporter::LoadAllMeshes(meshData);

	// Load meshes
	for (const MeshData& mData : meshData)
	{
		BinaryExporter::MeshData data;
		data.verts = mData.verticies;
		data.indicies = mData.indicies;
		data.vertCount = static_cast<int>(mData.verticies.size());
		data.indiCount = static_cast<int>(mData.indicies.size());

		BinaryExporter::MeshIndex index;
		index.id = std::hash<std::string>{}(mData.meshName);
		index.name = mData.meshName;
		index.size = sizeof(int) * 2 + sizeof(Vertex) * data.verts.size() + sizeof(unsigned) * data.indicies.size();

		myBinaryData.emplace_back(std::move(data));
		myIndex.emplace_back(std::move(index));
	}

	// Calculate header + full index block size (variable-length names!)
	int headerSize = sizeof(BinaryExporter::AssetHeader);
	int indexBlockSize = 0;
	for (const auto& idx : myIndex)
	{
		indexBlockSize += sizeof(size_t) + sizeof(int) + sizeof(int);      // id, offset, size
		indexBlockSize += sizeof(int) + static_cast<int>(idx.name.size()); // name length + name
	}

	int currentOffset = headerSize + indexBlockSize;
	for (size_t i = 0; i < myIndex.size(); ++i)
	{
		myIndex[i].offset = currentOffset;
		currentOffset += myIndex[i].size;
	}

	std::ofstream out(aOutDst, std::ios::binary);
	if (!out.is_open()) {
		std::cerr << "Failed to open mesh bundle file for writing." << std::endl;
		return;
	}

	// Write header
	BinaryExporter::AssetHeader header;
	header.totalAmount = static_cast<int>(myIndex.size());
	out.write(reinterpret_cast<const char*>(&header), sizeof(header));

	// Write index block
	for (const auto& idx : myIndex)
	{
		out.write(reinterpret_cast<const char*>(&idx.id), sizeof(size_t));
		out.write(reinterpret_cast<const char*>(&idx.offset), sizeof(int));
		out.write(reinterpret_cast<const char*>(&idx.size), sizeof(int));

		int nameLength = static_cast<int>(idx.name.size());
		out.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));
		out.write(idx.name.data(), nameLength);
	}

	// Write mesh data
	for (const auto& data : myBinaryData)
	{
		int vertSize = static_cast<int>(data.verts.size());
		int indexSize = static_cast<int>(data.indicies.size());
		out.write(reinterpret_cast<const char*>(&vertSize), sizeof(int));
		out.write(reinterpret_cast<const char*>(&indexSize), sizeof(int));

		out.write(reinterpret_cast<const char*>(data.verts.data()), sizeof(Vertex) * vertSize);
		out.write(reinterpret_cast<const char*>(data.indicies.data()), sizeof(unsigned) * indexSize);
	}

	out.close();
}
