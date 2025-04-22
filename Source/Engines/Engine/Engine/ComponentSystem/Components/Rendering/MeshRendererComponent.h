#pragma once

#include <Engine/ComponentSystem/Component.h>
#include <GraphicsEngine/Shader/Shaders/Shader.h>

#include <GraphicsEngine/GraphicsStructs.h>

enum TextureSlot
{
	Albedo, 
	Normal, 
	Material,
	COUNT
};

namespace Zengine::ComponentSystem
{
	class MeshRenderer final : public Component
	{
	public:
		void SetVertexShader(const char* aVertexShaderName);
		void SetPixelShader(const char* aPixelShaderName);

		void SetMesh(const char* aPixelShaderName);
		Mesh* GetMesh() const;

		const Zengine::Graphics::PixelShader* GetPixelShader()const;
		Zengine::Graphics::PixelShader* GetPixelShader();

		Zengine::Graphics::VertexShader* GetVertexShader();
		const Zengine::Graphics::VertexShader* GetVertexShader()const;

		void SetTexture(const std::string& aTexturePath, TextureSlot aSlot);
		std::string* GetTextures();

	private:
		Zengine::Graphics::Shader myShader = {};
		Mesh* myMesh;
		std::string myTextures[COUNT];
	};
}

namespace CS = Zengine::ComponentSystem;