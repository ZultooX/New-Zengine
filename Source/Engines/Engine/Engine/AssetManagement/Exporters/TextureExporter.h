#pragma once

#include <Engine/Editor/DebugLogger.h>

class Texture;
class TextureExporter final
{
public:
	/// <summary>
/// Exports the texture to a binary file.
/// </summary>
/// <param name="aOutDst">Will create a binary file at this path.</param>
/// <param name="aTexture">The texture it will export.</param>
	static void ExportToBinaryFile(const char* aOutDst, const Texture& aTexture);


	/// <summary>
	/// Will export all textures into binary format.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path, with all other textures inside.</param>
	static void ExportAllToBinaryFile(const char* aOutDst);
};

