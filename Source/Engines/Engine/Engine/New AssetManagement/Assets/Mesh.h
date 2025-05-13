#pragma once

#include "Asset.h"
#include <GraphicsEngine/GraphicsStructs.h>
#include <string>
namespace Assets
{
	class Mesh : public Asset
	{
		friend class MeshImporter;

	public:
		void SetMeshData(const MeshData& someMeshData);

		void AddSubMesh();
		SubMesh& GetLastSubmesh();

	public:
		const SubMesh& GetSubmesh(const unsigned& aIdx);
		const std::vector<SubMesh>& GetSubmeshes();

		bool HasSkeleton() const;
		const Skeleton* GetSkeleton() const; 

	private:
		MeshData myMesh;
	};
}