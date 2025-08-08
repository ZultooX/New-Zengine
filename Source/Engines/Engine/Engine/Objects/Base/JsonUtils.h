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

	inline constexpr const char* RoughnessKey = "roughness";
	inline constexpr const float RoughnessDefault = 0;

	inline constexpr const char* MetallicKey = "metallic";
	inline constexpr const float MetallicDefault = 0;

	inline constexpr const char* AOStrengthKey = "AOStrength";
	inline constexpr const float AOStrengthDefault = 0;

	inline constexpr const char* BloomIntensityKey = "BloomIntensity";
	inline constexpr const float BloomIntensityDefault = 0;

	inline constexpr const char* NormalStrengthKey = "NormalStrength";
	inline constexpr const float NormalStrengthDefault = 0;
}