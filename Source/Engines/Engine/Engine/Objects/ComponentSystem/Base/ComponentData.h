#pragma once

#include <vector>
#include <string>
#include <Zultools/Math/Vector3.hpp>
#include <Zultools/Math/Vector2.hpp>

class SerializedData
{
public:
	~SerializedData() { delete data; }

	void* data = nullptr;
	int size = 0;
};

struct ComponentData {
	int gameObjectID = 0;
	int bitmask = 0;
	int id = 0;

	std::string name = "";
};

struct TransformData : public ComponentData {
	Vector3f position;
	Vector3f scale;
	Vector3f eulerAngles;
};

struct MeshRendererData : public ComponentData {
	size_t meshID;
	std::vector<size_t> materialsIDs;
};

struct CameraData : public ComponentData {
	
	bool isMainCamera = false;

	float fov = 60.f;
	float nearPlane = 0.1f;
	float farPlane = 10000.f;

	Vector2f resolution = { 1920, 1080 };
	Vector2f size = { 1920, 1080 };

	int projectionType = 0;
};

struct EditorCameraData : public ComponentData {
	float movementSpeedScrollMultiplier = 1.f;
	float movementSpeedMultiplier = 3.f;
};
