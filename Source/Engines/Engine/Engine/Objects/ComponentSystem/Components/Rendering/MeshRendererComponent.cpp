#include "MeshRendererComponent.h"

#include <Engine/Utilities/MainSingleton.h>
#include <Engine/AssetManagement/AssetManager.h>

namespace Zengine::ComponentSystem
{



#pragma region [MESH]

	void MeshRenderer::SetMesh(const size_t& aMeshID)
	{
		myMesh = AssetManager::GetFromID<Mesh>(aMeshID);
	}

	const AssetPointer<Mesh>& MeshRenderer::GetMesh() const { return myMesh; }
	AssetPointer<Mesh>& MeshRenderer::GetMesh() { return myMesh; }

#pragma endregion


#pragma region [MATERIALS]

	void MeshRenderer::SetMaterial(const size_t& aMaterialID)
	{
		myMaterial = AssetManager::GetFromID<Material>(aMaterialID);
	}

	const AssetPointer<Material>& MeshRenderer::GetMaterial() const { return myMaterial; }

#pragma endregion
}