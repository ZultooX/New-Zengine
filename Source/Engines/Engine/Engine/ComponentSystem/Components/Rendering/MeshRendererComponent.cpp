#include "MeshRendererComponent.h"

#include <Engine/Utilities/MainSingleton.h>
#include <Engine/New AssetManagement/Manager/AssetManager.hpp>

namespace Zengine::ComponentSystem
{



#pragma region [MESH]

	void MeshRenderer::SetMesh(const char* aMeshName)
	{
		myMesh = AssetManager::GetFromPath<Assets::Mesh>(aMeshName);
	}

	Assets::Mesh* MeshRenderer::GetMesh() const { return myMesh; }

#pragma endregion


#pragma region [MATERIALS]

	void MeshRenderer::SetMaterial(const unsigned& aIdx, const std::string& aMaterialPath)
	{
		if (myMaterials.size() >= aIdx) return;

		myMaterials[aIdx] = aMaterialPath;
	}

	inline const std::string& MeshRenderer::GetMaterialAtIndex(const unsigned& aIdx) const
	{
		if (myMaterials.size() >= aIdx) return "";

		return myMaterials[aIdx];
	}

	const std::vector<std::string>& MeshRenderer::GetMaterials() { return myMaterials; }

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