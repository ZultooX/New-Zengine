#include "SceneImporter.h"

#include <Engine/ComponentSystem/GameObject.h>
#include <Engine/ComponentSystem/ComponentManager.h>
#include <Engine/ComponentSystem/GameObjectManager.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/EditorCamera.h>
#include <fstream>

void SceneImporter::Load(const size_t& aID, Scene& aOutAsset)
{
}

void SceneImporter::Load(const char* aPath, Scene& aOutAsset)
{
	std::ifstream out(aPath, std::ios::binary);
	if (!out.is_open()) return;

	using namespace Zengine::ComponentSystem;

#pragma region [GAMEOBJECTS]
	{
		int gameObjectsCount = 0;
		out.read(reinterpret_cast<char*>(&gameObjectsCount), sizeof(int));

		for (int i = 0; i < gameObjectsCount; ++i)
		{
			int id = 0, nameLength = 0, mask = 0;
			out.read(reinterpret_cast<char*>(&id), sizeof(int));

			out.read(reinterpret_cast<char*>(&nameLength), sizeof(int));
			std::string name(nameLength, ' ');
			out.read(name.data(), nameLength);

			out.read(reinterpret_cast<char*>(&mask), sizeof(int));

			GameObject* obj = GameObject::Create(id);
			obj->SetName(name);
			obj->SetBitmask(mask);
		}
	}
#pragma endregion


#pragma region [TRANSFORMS]
	{
		int transforms = 0;
		out.read(reinterpret_cast<char*>(&transforms), sizeof(int));

		for (int i = 0; i < transforms; ++i)
		{
			int owner;
			Vector3f pos, scale, rot;

			out.read(reinterpret_cast<char*>(&owner), sizeof(int));
			out.read(reinterpret_cast<char*>(&pos), sizeof(Vector3f));
			out.read(reinterpret_cast<char*>(&scale), sizeof(Vector3f));
			out.read(reinterpret_cast<char*>(&rot), sizeof(Vector3f));

			Transform* trans = GameObjectManager::GetGameObject(owner)->transform;
			trans->SetPosition(pos);
			trans->SetScale(scale);
			trans->SetEulerAngles(scale);
		}
	}
#pragma endregion


#pragma region [MESH RENDERERS]
	{
		int count = 0;
		out.read(reinterpret_cast<char*>(&count), sizeof(int));

		for (int i = 0; i < count; ++i)
		{
			int gameObjectID = 0;
			int materialCount = 0;
			std::vector<size_t> materialIds;
			size_t meshIds;

			out.read(reinterpret_cast<char*>(&gameObjectID), sizeof(int));
			MeshRenderer* rend = GameObjectManager::GetGameObject(gameObjectID)->AddComponent<MeshRenderer>();

			out.read(reinterpret_cast<char*>(&materialCount), sizeof(int));
			for (int i = 0; i < materialCount; ++i)
			{
				size_t matID = 0;
				out.read(reinterpret_cast<char*>(&matID), sizeof(size_t));

				//rend->AddMaterial(matID);
			}

			out.read(reinterpret_cast<char*>(&meshIds), sizeof(size_t));

			rend->SetMesh(meshIds);
		}
	}
#pragma endregion


#pragma region [EDITOR CAMERA]
	{
		int count = 0;
		out.read(reinterpret_cast<char*>(&count), sizeof(int));

		for (int i = 0; i < count; ++i)
		{
			int gameObjectID = 0;
			float movementScrollMultiplier = 0;
			float movementSpeedMultiplier = 0;
			out.read(reinterpret_cast<char*>(&gameObjectID), sizeof(int));
			out.read(reinterpret_cast<char*>(&movementScrollMultiplier), sizeof(int));
			out.read(reinterpret_cast<char*>(&movementSpeedMultiplier), sizeof(int));

			EditorCamera* eCam = GameObjectManager::GetGameObject(gameObjectID)->AddComponent<EditorCamera>();
			eCam->SetMovementSpeedMultiplier(movementSpeedMultiplier);
			eCam->SetScrollMultiplier(movementScrollMultiplier);
		}
	}
#pragma endregion


#pragma region [CAMERA]
	{
		int count = 0;
		out.read(reinterpret_cast<char*>(&count), sizeof(int));

		for (int i = 0; i < count; ++i)
		{
			int gameObjectID = 0;
			bool mainCamera = false, isOrthographics = false;
			float fov = 0, farPlane = 0, nearPlane = 0;
			Vector2f resolution, size;

			out.read(reinterpret_cast<char*>(&gameObjectID), sizeof(int));
			out.read(reinterpret_cast<char*>(&mainCamera), sizeof(bool));
			out.read(reinterpret_cast<char*>(&fov), sizeof(float));
			out.read(reinterpret_cast<char*>(&nearPlane), sizeof(float));
			out.read(reinterpret_cast<char*>(&farPlane), sizeof(float));
			out.read(reinterpret_cast<char*>(&resolution), sizeof(Vector2f));
			out.read(reinterpret_cast<char*>(&size), sizeof(Vector2f));
			out.read(reinterpret_cast<char*>(&isOrthographics), sizeof(bool));

			Camera* cam = GameObjectManager::GetGameObject(gameObjectID)->AddComponent<Camera>();
			cam->fov = fov;
			cam->nearPlane = nearPlane;
			cam->farPlane = farPlane;
			cam->resolution = resolution;
			cam->size = size;

			cam->isMainCamera = mainCamera;
			if (mainCamera)
			{
				cam->MainCamera = cam;
			}
			cam->isOrhographics = isOrthographics;
		}
	}
#pragma endregion

}

void SceneImporter::Unload(Scene& aOutAsset)
{
}