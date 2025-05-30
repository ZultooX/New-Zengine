#pragma once

namespace Json
{
	namespace Color
	{
		inline constexpr const char* Key = "color";
		inline constexpr const char* R = "r";
		inline constexpr const char* G = "g";
		inline constexpr const char* B = "b";
		inline constexpr const char* A = "a";

		inline constexpr float DefaultR = 1.0f;
		inline constexpr float DefaultG = 1.0f;
		inline constexpr float DefaultB = 1.0f;
		inline constexpr float DefaultA = 1.0f;
	}

	inline constexpr const char* TexturesKey = "Textures";

	inline constexpr const char* VertexShaderKey = "sh_vertex";
	inline constexpr const char* VertexShaderDefault = ZENGINE_SHADERS_PATH"VS_Default.cso";

	inline constexpr const char* PixelShaderKey = "sh_pixel";
	inline constexpr const char* PixelShaderDefault = ZENGINE_SHADERS_PATH"PS_Default.cso";

}