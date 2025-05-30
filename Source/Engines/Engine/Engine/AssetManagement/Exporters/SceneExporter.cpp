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

	const std::vector<Transform*> transforms = ComponentManager::GetComponents<Transform>();
	int size = (int)transforms.size();
	out.write(reinterpret_cast<const char*>(&size), sizeof(int));
	for (const Transform* trans : transforms)
	{
		Vector3f position = trans->GetPosition();
		Vector3f scale = trans->GetScale();
		Vector3f eulerAngles = trans->GetEulerAngles();
		int owner= trans->gameobject->GetID();
		
		out.write(reinterpret_cast<const char*>(&owner), sizeof(int));
		out.write(reinterpret_cast<const char*>(&position), sizeof(Vector3f));
		out.write(reinterpret_cast<const char*>(&scale), sizeof(Vector3f));
		out.write(reinterpret_cast<const char*>(&eulerAngles), sizeof(Vector3f));
	}

	out.write(reinterpret_cast<const char*>(&ComponentManager::GetComponents<MeshRenderer>()), sizeof(int));
	for (MeshRenderer* mRenderer : ComponentManager::GetComponents<MeshRenderer>())
	{
		out.write(reinterpret_cast<const char*>(&mRenderer->gameobject->GetID()), sizeof(size_t));

		for (const AssetPointer<Material>& mat : mRenderer->GetMaterials())
		{
			out.write(reinterpret_cast<const char*>(&mat->GetID()), sizeof(size_t));
		}

		out.write(reinterpret_cast<const char*>(&mRenderer->GetMesh()->GetID()), sizeof(size_t));
	}

	out.write(reinterpret_cast<const char*>(&ComponentManager::GetComponents<EditorCamera>()), sizeof(int));
	for (EditorCamera* eCam : ComponentManager::GetComponents<EditorCamera>())
	{
		out.write(reinterpret_cast<const char*>(&eCam->gameobject->GetID()), sizeof(size_t));
		out.write(reinterpret_cast<const char*>(&eCam->myMovementSpeedScrollMultiplier), sizeof(float));
		out.write(reinterpret_cast<const char*>(&eCam->myMovementSpeedMultiplier), sizeof(float));
	}

	out.write(reinterpret_cast<const char*>(&ComponentManager::GetComponents<Camera>()), sizeof(int));
	for (Camera* cam : ComponentManager::GetComponents<Camera>())
	{
		out.write(reinterpret_cast<const char*>(&cam->gameobject->GetID()), sizeof(size_t));
		out.write(reinterpret_cast<const char*>(&cam->isMainCamera), sizeof(bool));
		out.write(reinterpret_cast<const char*>(&cam->fov), sizeof(float));
		out.write(reinterpret_cast<const char*>(&cam->nearPlane), sizeof(float));
		out.write(reinterpret_cast<const char*>(&cam->farPlane), sizeof(float));
		out.write(reinterpret_cast<const char*>(&cam->resolution), sizeof(Vector2f));
		out.write(reinterpret_cast<const char*>(&cam->size), sizeof(Vector2f));
		out.write(reinterpret_cast<const char*>(&cam->isOrhographics), sizeof(bool));
	}
}
