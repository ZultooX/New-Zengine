#include "MeshRendererComponent.h"

#include <Engine/Utilities/MainSingleton.h>
#include <Engine/AssetManagement/AssetManager.h>

namespace Zengine::ComponentSystem
{



#pragma region [MESH]

	void MeshRenderer::SetMesh(const char* aMeshName)
	{
		myMesh = AssetManager::Get<Mesh>(aMeshName);
	}

	AssetPointer<Mesh>& MeshRenderer::GetMesh() { return myMesh; }

#pragma endregion


#pragma region [MATERIALS]

	void MeshRenderer::AddMaterial(const std::string& aMaterialPath)
	{
		AssetPointer<Material> mat = AssetManager::Get<Material>(aMaterialPath.c_str());
		myMaterials.push_back(mat);
	}

	void MeshRenderer::SetMaterial(const unsigned& aIdx, const std::string& aMaterialPath)
	{
		if (myMaterials.size() >= aIdx) return;

		myMaterials[aIdx] = AssetManager::Get<Material>(aMaterialPath.c_str());
	}

	inline const AssetPointer<Material>& MeshRenderer::GetMaterialAtIndex(const unsigned& aIdx) const
	{
		if (myMaterials.size() >= aIdx) return {};

		return myMaterials[aIdx];
	}

	const std::vector<AssetPointer<Material>>& MeshRenderer::GetMaterials() { return myMaterials; }

	void MeshRenderer::RemoveMaterialAtIndex(const unsigned& aIdx)
	{
		if (myMaterials.size() >= aIdx) return;
		
		myMaterials.erase(myMaterials.begin() + aIdx);
	}

	void MeshRenderer::ClearMaterials()
	{
		myMaterials.clear();
	}

#pragma endregion


}