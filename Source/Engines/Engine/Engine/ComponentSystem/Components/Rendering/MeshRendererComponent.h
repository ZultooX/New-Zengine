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
#pragma region [MESH]
		void SetMesh(const char* aMeshName);
		void SetMesh(const size_t& aMeshID);
		const AssetPointer<Mesh>& GetMesh() const;
		AssetPointer<Mesh>& GetMesh();
#pragma endregion

#pragma region [MATERIAL]
		void SetMaterial(const std::string& aMaterialPath);
		void SetMaterial(const size_t& aMaterialID);

		const AssetPointer<Material>& GetMaterial() const;
#pragma endregion



	private:
		AssetPointer<Material> myMaterial;
		AssetPointer<Mesh> myMesh;
	};
}

namespace CS = Zengine::ComponentSystem;