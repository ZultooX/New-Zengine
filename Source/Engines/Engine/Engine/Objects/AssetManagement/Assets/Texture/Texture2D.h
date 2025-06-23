#pragma once

#include <Engine/Objects/AssetManagement/Assets/Texture.h>
#include <Zultools/Math/Color.h>

#include <vector>

struct ID3D11Texture2D;
namespace Zengine
{
	class Texture2D final : public Texture
	{
		friend class Texture2DLoader;

	public:
		Texture2D(const unsigned& _width, const unsigned& _height, 
			const TextureFormat& _format = FORMAT_R8G8B8A8_UNORM_SRGB);
		Texture2D(const unsigned& _width, const unsigned& _height, std::vector<unsigned char>& _defaultData, 
			const TextureFormat& _format = FORMAT_R8G8B8A8_UNORM_SRGB);

		Texture2D();
		Texture2D(const size_t& _id);
		virtual ~Texture2D() = default;

	public:
		void SetPixel(const unsigned& _x, const unsigned& _y, const Color& color);
		void Apply();

	public:
		const std::vector<unsigned char>& GetData() const;
		std::vector<unsigned char>& GetData();
		void SetData(std::vector<unsigned char>& data);

	private:
		void CreateTexture();

	public:
		const ID3D11Texture2D* GetTexture() const;
		ID3D11Texture2D* GetTexture();
		ID3D11Texture2D** GetTextureAddr();

	private:
		ID3D11Texture2D* texture = nullptr;

		std::vector<unsigned char> pixelData;
		unsigned width = 0, height =0 ;
		TextureFormat format;
	};
}