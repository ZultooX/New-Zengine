#pragma once

#include <Engine/ComponentSystem/Component.h>

#include <GraphicsEngine/GraphicsStructs.h>
#include <GraphicsEngine/Model/Model.h>

#include <Engine/AssetManagement/Assets/Mesh.h>
#include <Engine/AssetManagement/Assets/Material.h>
#include <Engine/AssetManagement/Base/AssetPointer.h>

namespace Zengine::ComponentSystem
{
	class MeshRenderer final : public Component
	{
		COMPONENT_BASICS(MeshRenderer)

	public:
		void SetMesh(const char* aPixelShaderName);
		AssetPointer<Mesh>& GetMesh();


		void AddMaterial(const std::string& aMaterialPath);
		void SetMaterial(const unsigned& aIdx, const std::string& aMaterialPath);

		const AssetPointer<Material>& GetMaterialAtIndex(const unsigned& aIdx) const;
		const std::vector<AssetPointer<Material>>& GetMaterials();

		void RemoveMaterialAtIndex(const unsigned& aIdx);
		void ClearMaterials();

	private:
		std::vector<AssetPointer<Material>> myMaterials;
		AssetPointer<Mesh> myMesh;
	};
}

namespace CS = Zengine::ComponentSystem;