#pragma once

#include <Engine/ComponentSystem/Component.h>
#include <GraphicsEngine/Shader/Shaders/Shader.h>

#include <GraphicsEngine/GraphicsStructs.h>
#include <GraphicsEngine/DX11/Model/Model.h>

namespace Zengine::ComponentSystem
{
	class MeshRenderer final : public Component
	{
	public:
		void SetMesh(const char* aPixelShaderName);
		Mesh* GetMesh() const;


		inline void AddMaterial(const std::string& aMaterialPath) { myMaterials.push_back(aMaterialPath); }
		void SetMaterial(const unsigned& aIdx, const std::string& aMaterialPath);

		const std::string& GetMaterialAtIndex(const unsigned& aIdx) const;
		const std::vector<std::string>& GetMaterials();

		void RemoveMaterialAtIndex(const unsigned& aIdx);
		void ClearMaterials();

	private:
		std::vector<std::string> myMaterials;
		Mesh* myMesh;
	};
}

namespace CS = Zengine::ComponentSystem;