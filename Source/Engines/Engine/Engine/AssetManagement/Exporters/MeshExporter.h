#pragma once

class Mesh;
class MeshExporter
{

public:
	/// <summary>
	/// Exports the shader to a binary file.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path.</param>
	/// <param name="aMesh">The mesh it will export.</param>
	static void ExportToBinaryFile(const char* aOutDst, const Mesh& aMesh);


	/// <summary>
	/// Will export all meshes into binary format.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path, with all other shaders inside.</param>
	static void ExportAllToBinaryFile(const char* aOutDst);
};

