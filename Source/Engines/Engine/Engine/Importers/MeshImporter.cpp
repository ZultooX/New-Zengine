#include "MeshImporter.h"

//#include <Engine/Editor/DebugLogger.h>
//
//#include <GraphicsEngine/GraphicsEngine.h>
//#include <Engine/Engine.h>
//
//fbxsdk::FbxManager* MeshImporter::myFbxManager;
//fbxsdk::FbxAxisSystem MeshImporter::myAxisSystem;
//fbxsdk::FbxGeometryConverter* MeshImporter::myGeometryConverter;
//
//void MeshImporter::Init()
//{
//	myFbxManager = FbxManager::Create();
//	FbxIOSettings* ios = FbxIOSettings::Create(myFbxManager, IOSROOT);
//	ios->SetBoolProp(IMP_FBX_TEXTURE, false);
//	ios->SetBoolProp(IMP_FBX_EXTRACT_EMBEDDED_DATA, false);
//
//	myGeometryConverter = new FbxGeometryConverter(myFbxManager);
//
//	myFbxManager->SetIOSettings(ios);
//
//	myAxisSystem = FbxAxisSystem::eDirectX;
//}
//
//
//Mesh* MeshImporter::Load(const std::string& aMeshPath)
//{
//	FbxImporter* importer = FbxImporter::Create(myFbxManager, "");
//	FbxScene* scene = FbxScene::Create(myFbxManager, "scene");
//
//
//	myGeometryConverter->Triangulate(scene, true);
//
//
//	//for (int i = 0; i < scene->GetNodeCount(); ++i)
//	//{
//	//	FbxNode* node = scene->GetNode(i);
//	//	FbxMesh* mesh = node->GetMesh();
//	//	
//	//	//mesh->InitTextureUV(1);
//	//	//mesh->GenerateNormals();
//	//	mesh->GenerateTangentsData(0);
//	//}
//
//
//
//	myAxisSystem.DeepConvertScene(scene);
//
//	if (!importer->Initialize(aMeshPath.c_str(), -1, myFbxManager->GetIOSettings())) {
//		DebugLogger::LogWarning(aMeshPath + " | Not found.");
//		return nullptr;
//	}
//
//	if (!importer->Import(scene)) {
//		DebugLogger::LogWarning("Failed to import scene.");
//		importer->Destroy();
//		return nullptr;
//	}
//
//	importer->Destroy();
//
//	FbxNode* root = scene->GetRootNode();
//	if (!root)
//	{
//		DebugLogger::LogWarning("Scene has no root node.");
//		return nullptr;
//	}
//
//
//	Mesh* mesh = new Mesh();
//	for (int i = 0; i < root->GetChildCount(); ++i)
//	{
//		FbxNode* node = root->GetChild(i);
//		mesh->meshes.push_back(ProcessMesh(node->GetMesh()));
//	}
//
//	return mesh;
//}
//
//SubMesh MeshImporter::ProcessMesh(FbxMesh* aNode)
//{
//	SubMesh mesh = SubMesh();
//
//	std::unordered_map < size_t, unsigned> verticeToIdx;
//
//	unsigned IndexCounter = 0;
//
//	for (unsigned p = 0; p < aNode->GetPolygonCount(); p++)
//	{
//		for (unsigned v = 0; v < 3; v++)
//		{
//			int idx = aNode->GetPolygonVertex(p, v);
//			const fbxsdk::FbxVector4 position = aNode->GetControlPointAt(idx);
//
//			aNode->GenerateNormals();
//			aNode->GenerateTangentsData(0);
//
//			Vertex vert;
//			vert.position = Vector4f(position[0], position[1], position[2], position[3]);
//
//			FbxVector4 normal;
//			aNode->GetPolygonVertexNormal(p, v, normal);
//			vert.normal = Vector3f(normal[0], normal[1], normal[2]);
//
//			const FbxGeometryElementTangent* tangents = aNode->GetElementTangent();
//			if (tangents && tangents->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				FbxVector4 tangent = tangents->GetDirectArray().GetAt(aNode->GetPolygonVertexIndex(p) + v);
//				vert.tangent = Vector3f(tangent[0], tangent[1], tangent[2]);
//			}
//
//			const FbxGeometryElementBinormal* binormal = aNode->GetElementBinormal();
//			if (tangents && tangents->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				FbxVector4 tangent = tangents->GetDirectArray().GetAt(aNode->GetPolygonVertexIndex(p) + v);
//				vert.tangent = Vector3f(tangent[0], tangent[1], tangent[2]);
//			}
//
//			size_t hashedVert = HashVertice(vert);
//
//			if (verticeToIdx.find(hashedVert) == verticeToIdx.end())
//			{
//				verticeToIdx[hashedVert] = IndexCounter;
//
//				mesh.indicies.push_back(IndexCounter++);
//				mesh.verticies.push_back(vert);
//			}
//			else
//			{
//				mesh.indicies.push_back(verticeToIdx[hashedVert]);
//			}
//		}
//	}
//
//	DX11GraphicsEngine* ge = dynamic_cast<DX11GraphicsEngine*>(Engine::GetGraphicsEngine());
//	{
//		D3D11_BUFFER_DESC indexBufferDesc = {};
//		indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
//		indexBufferDesc.ByteWidth = (unsigned)(sizeof(unsigned) * mesh.indicies.size());
//		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//
//		D3D11_SUBRESOURCE_DATA indexData = { 0 };
//		indexData.pSysMem = mesh.indicies.data();
//
//		ge->CreateBuffer(&mesh.indexBuffer, indexBufferDesc, indexData);
//	}
//
//	{
//		D3D11_BUFFER_DESC vertexBufferDesc = {};
//		vertexBufferDesc.ByteWidth = (unsigned)(sizeof(Vertex) * mesh.verticies.size());
//		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
//		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//
//		D3D11_SUBRESOURCE_DATA vertexData = { 0 };
//		vertexData.pSysMem = mesh.verticies.data();
//
//		ge->CreateBuffer(&mesh.vertexBuffer, vertexBufferDesc, vertexData);
//	}
//
//	return mesh;
//}
//
//Skeleton* MeshImporter::ProcessSkeleton(const FbxSkeleton* aNode)
//{
//	return nullptr;
//}
//
//size_t MeshImporter::HashVertice(const Vertex& aVertex)
//{
//	std::size_t value = 0;
//
//	// Position
//	{
//		HashCombine(value, aVertex.position.x);
//		HashCombine(value, aVertex.position.y);
//		HashCombine(value, aVertex.position.z);
//	}
//
//	// Normals
//	{
//		HashCombine(value, aVertex.normal.x);
//		HashCombine(value, aVertex.normal.y);
//		HashCombine(value, aVertex.normal.z);
//
//		HashCombine(value, aVertex.binormal.x);
//		HashCombine(value, aVertex.binormal.y);
//		HashCombine(value, aVertex.binormal.z);
//
//		HashCombine(value, aVertex.tangent.x);
//		HashCombine(value, aVertex.tangent.y);
//		HashCombine(value, aVertex.tangent.z);
//	}
//
//	// Color
//	{
//		HashCombine(value, aVertex.color0.x);
//		HashCombine(value, aVertex.color0.y);
//		HashCombine(value, aVertex.color0.z);
//		HashCombine(value, aVertex.color0.w);
//
//		HashCombine(value, aVertex.color1.x);
//		HashCombine(value, aVertex.color1.y);
//		HashCombine(value, aVertex.color1.z);
//		HashCombine(value, aVertex.color1.w);
//
//		HashCombine(value, aVertex.color2.x);
//		HashCombine(value, aVertex.color2.y);
//		HashCombine(value, aVertex.color2.z);
//		HashCombine(value, aVertex.color2.w);
//
//		HashCombine(value, aVertex.color3.x);
//		HashCombine(value, aVertex.color3.y);
//		HashCombine(value, aVertex.color3.z);
//		HashCombine(value, aVertex.color3.w);
//	}
//
//	// UVs
//	{
//		HashCombine(value, aVertex.uv0.x);
//		HashCombine(value, aVertex.uv0.y);
//
//		HashCombine(value, aVertex.uv1.x);
//		HashCombine(value, aVertex.uv1.y);
//		
//		HashCombine(value, aVertex.uv2.x);
//		HashCombine(value, aVertex.uv2.y);
//
//		HashCombine(value, aVertex.uv3.x);
//		HashCombine(value, aVertex.uv3.y);
//	}
//
//	// Bones
//	{ 
//		HashCombine(value, aVertex.boneIDs.x);
//		HashCombine(value, aVertex.boneIDs.y);
//		HashCombine(value, aVertex.boneIDs.z);
//		HashCombine(value, aVertex.boneIDs.w);
//
//		HashCombine(value, aVertex.boneWeights.x);
//		HashCombine(value, aVertex.boneWeights.y);
//		HashCombine(value, aVertex.boneWeights.z);
//		HashCombine(value, aVertex.boneWeights.w);
//	}
//
//	return value;
//}
