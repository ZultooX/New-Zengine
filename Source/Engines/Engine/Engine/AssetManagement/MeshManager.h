#pragma once
#include "AssetManager.h"

#include <GraphicsEngine/GraphicsStructs.h>

namespace TGA::FBX
{
	struct Mesh;
}

class MeshManager final : public AbstractAssetManager<Mesh>
{
public:
	void Init() override;

protected:
	Mesh* Load(const std::string& aMeshPath) override;

private:
	void ConvertFromTGAMesh(const TGA::FBX::Mesh& aMesh, Mesh* aOutMesh);
};