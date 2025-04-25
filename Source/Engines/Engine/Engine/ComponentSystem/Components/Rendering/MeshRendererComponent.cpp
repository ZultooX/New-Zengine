#include "MeshRendererComponent.h"

#include <Engine/Utilities/MainSingleton.h>
#include <Engine/AssetManagement/MeshManager.h>

namespace Zengine::ComponentSystem
{
	void MeshRenderer::SetMesh(const char* aMeshName)
	{
		myMesh = MainSingleton::GetInstance<MeshManager>().Get(aMeshName);
	}

	Mesh* MeshRenderer::GetMesh() const { return myMesh; }

	const std::vector<std::string>& MeshRenderer::GetMaterials() { return myMaterials; }
	
}