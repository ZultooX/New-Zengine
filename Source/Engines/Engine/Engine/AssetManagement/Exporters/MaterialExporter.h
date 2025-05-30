#pragma once

class Material;
class MaterialExporter
{
public:
	static void CreateNewMaterialFile(const char* aOutDst, const Material& aMaterial);

public:
	/// <summary>
	/// Exports the shader to a binary file.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path.</param>
	/// <param name="aMaterial">The material it will export.</param>
	static void ExportToBinaryFile(const char* aOutDst, const Material& aMaterial);


	/// <summary>
	/// Will export all meshes into binary format.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path, with all other shaders inside.</param>
	static void ExportAllToBinaryFile(const char* aOutDst);
};

