#include "MeshRendererComponent.h"

#include <Engine/Utilities/MainSingleton.h>
#include <Engine/AssetManagement/AssetManager.h>

namespace Zengine::ComponentSystem
{



#pragma region [MESH]

	void MeshRenderer::SetMesh(const char* aMeshName)
	{
		myMesh = AssetManager::GetFromPath<Mesh>(aMeshName);
	}

	void MeshRenderer::SetMesh(const size_t& aMeshID)
	{
		myMesh = AssetManager::GetFromID<Mesh>(aMeshID);
	}

	const AssetPointer<Mesh>& MeshRenderer::GetMesh() const { return myMesh; }
	AssetPointer<Mesh>& MeshRenderer::GetMesh() { return myMesh; }

#pragma endregion


#pragma region [MATERIALS]

	void MeshRenderer::SetMaterial(const std::string& aMaterialPath)
	{
		myMaterial = AssetManager::Get<Material>(aMaterialPath.c_str());
	}

	void MeshRenderer::SetMaterial(const size_t& aMaterialID)
	{
		myMaterial = AssetManager::Get<Material>(aMaterialID);
	}

	const AssetPointer<Material>& MeshRenderer::GetMaterial() const { return myMaterial; }

#pragma endregion
}