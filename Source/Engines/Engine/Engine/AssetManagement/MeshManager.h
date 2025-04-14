#include "AssetManager.h"

#include <GraphicsEngine/GraphicsStructs.h>
#include <FBXSDK/fbxsdk.h>

class MeshManager final : public AbstractAssetManager<Mesh>
{
public:
	void Init() override;
	Mesh* Load(const std::string& aMeshPath) override;
};