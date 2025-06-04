#include "SceneExporter.h"

#include <Engine/ComponentSystem/ComponentManager.h>
#include <Engine/ComponentSystem/GameObjectManager.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/Camera.h>
#include <Engine/ComponentSystem/Components/Rendering/Camera/EditorCamera.h>
#include <fstream>

void SceneExporter::SaveScene(const char* aOutDst)
{
	std::ofstream out(aOutDst, std::ios::binary);
	if (!out.is_open()) return;

	using namespace Zengine::ComponentSystem;
	int gameObjectsCount = (int)GameObjectManager::GetGameObjects().size();
	out.write(reinterpret_cast<const char*>(&gameObjectsCount), sizeof(int));

	for (const auto& [id, obj] : GameObjectManager::GetGameObjects())
	{
		out.write(reinterpret_cast<const char*>(&obj->GetID()), sizeof(int));

		int nameLength = (int)obj->GetName().size();
		out.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));
		out.write(obj->GetName().data(), nameLength);

		out.write(reinterpret_cast<const char*>(&obj->GetBitmask().GetMask()), sizeof(int));
	}

	{ // Transforms
		const std::vector<Transform*> compList = ComponentManager::GetComponents<Transform>();
		int size = (int)compList.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(int));
		for (const Transform* comp : compList)
		{
			const Vector3f& position = comp->GetPosition();
			const Vector3f& scale = comp->GetScale();
			const Vector3f& eulerAngles = comp->GetEulerAngles();
			const int& owner = comp->gameobject->GetID();

			out.write(reinterpret_cast<const char*>(&owner), sizeof(int));
			out.write(reinterpret_cast<const char*>(&position), sizeof(Vector3f));
			out.write(reinterpret_cast<const char*>(&scale), sizeof(Vector3f));
			out.write(reinterpret_cast<const char*>(&eulerAngles), sizeof(Vector3f));
		}
	}


	{ // Meshrenderers
		//const std::vector<MeshRenderer*> compList = ComponentManager::GetComponents<MeshRenderer>();
		//int size = (int)compList.size();
		//out.write(reinterpret_cast<const char*>(&size), sizeof(int));
		//for (const MeshRenderer* comp : compList)
		//{
		//	out.write(reinterpret_cast<const char*>(&comp->gameobject->GetID()), sizeof(int));

		//	int materialCount = (int)comp->GetMaterials().size();
		//	out.write(reinterpret_cast<const char*>(&materialCount), sizeof(int));
		//	for (const AssetPointer<Material>& mat : comp->GetMaterials())
		//	{
		//		out.write(reinterpret_cast<const char*>(&mat->GetID()), sizeof(size_t));
		//	}

		//	out.write(reinterpret_cast<const char*>(&comp->GetMesh()->GetID()), sizeof(size_t));
		//}
	}


	{ // Editor Camera
		const std::vector<EditorCamera*> compList = ComponentManager::GetComponents<EditorCamera>();
		int size = (int)compList.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(int));
		for (const EditorCamera* comp : compList)
		{
			out.write(reinterpret_cast<const char*>(&comp->gameobject->GetID()), sizeof(int));
			out.write(reinterpret_cast<const char*>(&comp->myMovementSpeedScrollMultiplier), sizeof(float));
			out.write(reinterpret_cast<const char*>(&comp->myMovementSpeedMultiplier), sizeof(float));
		}
	}


	{ // Camera
		const std::vector<Camera*> compList = ComponentManager::GetComponents<Camera>();
		int size = (int)compList.size();
		out.write(reinterpret_cast<const char*>(&size), sizeof(int));
		for (const Camera* comp : compList)
		{
				out.write(reinterpret_cast<const char*>(&comp->gameobject->GetID()), sizeof(int));
				out.write(reinterpret_cast<const char*>(&comp->isMainCamera), sizeof(bool));
				out.write(reinterpret_cast<const char*>(&comp->fov), sizeof(float));
				out.write(reinterpret_cast<const char*>(&comp->nearPlane), sizeof(float));
				out.write(reinterpret_cast<const char*>(&comp->farPlane), sizeof(float));
				out.write(reinterpret_cast<const char*>(&comp->resolution), sizeof(Vector2f));
				out.write(reinterpret_cast<const char*>(&comp->size), sizeof(Vector2f));
				out.write(reinterpret_cast<const char*>(&comp->isOrhographics), sizeof(bool));
		}
	}
}
