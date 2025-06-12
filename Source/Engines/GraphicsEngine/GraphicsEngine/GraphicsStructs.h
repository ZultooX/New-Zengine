#pragma once

#include <vector>
#include <Zultools/Math/Matrix4x4.hpp>
#include <Zultools/Math/Vector4.hpp>
#include <Zultools/Math/Vector3.hpp>
#include <Zultools/Math/Vector2.hpp>

#include <d3d11.h>

struct Bone {
	Matrix4x4f jointTransform;
	int parendIdx = -1;
	std::string nameSpaceName;
	std::string Name;
	std::vector<unsigned> children;
};

struct Skeleton
{
	std::string name;

	std::vector<Bone> bones;
	std::unordered_map<std::string, size_t> boneNameToIdx;
};

struct Vertex {
	Vector4f position;

	Vector4f color0;
	Vector4f color1;
	Vector4f color2;
	Vector4f color3;

	Vector2f uv0;
	Vector2f uv1;
	Vector2f uv2;
	Vector2f uv3;

	Vector3f normal;
	Vector3f tangent;
	Vector3f binormal;

	Vector4Int boneIDs;
	Vector4f boneWeights;
};

struct SubMesh {
	std::string meshName;
	unsigned int materialIndex;

	std::vector<Vertex> verticies;
	std::vector<unsigned> indicies;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
};

