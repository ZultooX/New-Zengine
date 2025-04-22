#pragma once

//#include <FBXSDK/fbxsdk.h>
//
//#include <GraphicsEngine/GraphicsStructs.h>
//#include <string>
//
//class MeshImporter {
//public:
//	static void Init();
//	static Mesh* Load(const std::string& aMeshPath);
//
//private:
//	static SubMesh ProcessMesh(FbxMesh* aNode);
//	static Skeleton* ProcessSkeleton(const FbxSkeleton* aNode);
//
//	static size_t HashVertice(const Vertex& aVertex);
//
//private:
//	static fbxsdk::FbxManager* myFbxManager;
//	static fbxsdk::FbxAxisSystem myAxisSystem;
//	static fbxsdk::FbxGeometryConverter* myGeometryConverter;
//
//private:
//	template <class T>
//	static inline void HashCombine(std::size_t& inOutResult, const T& aValue)
//	{
//		std::hash<T> hasher;
//		inOutResult ^= hasher(aValue) + 0x9e3779b9 + (inOutResult << 6) + (inOutResult >> 2);
//	}
//};