#pragma once

class Scene;
class SceneExporter final
{
public:
	static void SaveScene(const char* aOutDst);
	



	/// <summary>
	/// Exports the shader to a binary file.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path.</param>
	/// <param name="aVertexShader">The shader it will export.</param>
	static void ExportToBinaryFile(const char* aOutDst, const Scene& aScene);


	/// <summary>
	/// Will export all vertex shaders into binary format.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path, with all other shaders inside.</param>
	static void ExportAllToBinaryFile(const char* aOutDst);
};

