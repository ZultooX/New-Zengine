#pragma once

#include <string>
#include <unordered_map>

#define  VERTEX_SHADER_ENTRY vs_main
#define  PIXEL_SHADER_ENTRY ps_main



inline std::unordered_map<std::string, unsigned> inputLayoutVariablesTypes = 
{
	{"SV_POSITION", 2},

	{"COLOR", 2},
	{"UV", 16},

	{"NORMAL", 6},
	{"TANGENT", 6},
	{"BINORMAL", 6},

	{"BONES", 3},
	{"BONEWEIGHTS", 2},
};