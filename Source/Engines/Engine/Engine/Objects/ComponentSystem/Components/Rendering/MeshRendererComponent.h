#pragma once

#include <Engine/Objects/ComponentSystem/Component.h>

#include <GraphicsEngine/GraphicsStructs.h>
#include <GraphicsEngine/Model/Model.h>

#include <Engine/Objects/AssetManagement/Assets/Mesh.h>
#include <Engine/Objects/AssetManagement/Assets/Material.h>
#include <Engine/Objects/Base/AssetPointer.hpp>

namespace Zengine
{
	class MeshRenderer final : public Component
	{
		COMPONENT_BASICS(MeshRenderer)

	public:
#pragma region [MESH]
		void SetMesh(const size_t& aMeshID);
		const AssetPointer<Mesh>& GetMesh() const;
		AssetPointer<Mesh>& GetMesh();
#pragma endregion

#pragma region [MATERIAL]
		void SetMaterial(const size_t& aMaterialID);

		const AssetPointer<Material>& GetMaterial() const;
#pragma endregion



	private:
		AssetPointer<Material> myMaterial;
		AssetPointer<Mesh> myMesh;
	};
}

namespace CS = Zengine::ComponentSystem;