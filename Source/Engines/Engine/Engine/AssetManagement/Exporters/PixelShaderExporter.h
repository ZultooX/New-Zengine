#pragma once

class PixelShader;
class PixelShaderExporter
{
public:
	/// <summary>
	/// Exports the shader to a binary file.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path.</param>
	/// <param name="aPixelShader">The shader it will export.</param>
	static void ExportToBinaryFile(const char* aOutDst, const PixelShader& aPixelShader);


	/// <summary>
	/// Will export all pixel shaders into binary format.
	/// </summary>
	/// <param name="aOutDst">Will create a binary file at this path, with all other shaders inside.</param>
	static void ExportAllToBinaryFile(const char* aOutDst);
};

