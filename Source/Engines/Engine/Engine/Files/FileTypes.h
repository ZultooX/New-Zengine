#pragma once

#include <unordered_map>
#include <string>

enum class FileTypes
{
	MESH,
	TEXTURE,
	MATERIAL
};

std::unordered_map<std::string, FileTypes> fileExtensionToType =
{
	{"fbx", FileTypes::MESH},
	{".fbx", FileTypes::MESH},
	{"obj", FileTypes::MESH},
	{".obj", FileTypes::MESH},

#pragma region [Textures]

	{".jpeg", FileTypes::TEXTURE},
	{"jpeg", FileTypes::TEXTURE},

	{".png", FileTypes::TEXTURE},
	{"png", FileTypes::TEXTURE},

	{".tga", FileTypes::TEXTURE},
	{"tga", FileTypes::TEXTURE},

	{".bmp", FileTypes::TEXTURE},
	{"bmp", FileTypes::TEXTURE},

	{".psd", FileTypes::TEXTURE},
	{"psd", FileTypes::TEXTURE},

	{".gif", FileTypes::TEXTURE},
	{"gif", FileTypes::TEXTURE},

	{".hdr", FileTypes::TEXTURE},
	{"hdr", FileTypes::TEXTURE},

	{".pic", FileTypes::TEXTURE},
	{"pic", FileTypes::TEXTURE},

	{".pnm", FileTypes::TEXTURE},
	{"pnm", FileTypes::TEXTURE},

	{".dds", FileTypes::TEXTURE},
	{"dds", FileTypes::TEXTURE},

#pragma endregion

	{".mat", FileTypes::MATERIAL},
	{"mat", FileTypes::MATERIAL},
};