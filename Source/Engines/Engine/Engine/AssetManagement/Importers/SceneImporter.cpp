#include "SceneImporter.h"

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
	int gameObjectsCount = 0;
	out.read(reinterpret_cast<char*>(&gameObjectsCount), sizeof(int));


	for (int i = 0; i < gameObjectsCount; ++i)
	{
		int id = 0;
		out.read(reinterpret_cast<char*>(&id), sizeof(int));

		GameObject* obj = GameObject::Create(id);


		std::string name;
		int nameLength = 0;
		out.read(reinterpret_cast<char*>(&nameLength), sizeof(int));

		name.resize(nameLength);
		out.read(name.data(), nameLength);

		obj->myName = name;

		int bitmask = obj->GetBitmask().GetMask();
		out.read(reinterpret_cast<char*>(&bitmask), sizeof(int));

		obj->SetBitmask(bitmask);
	}

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

void SceneImporter::Unload(Scene& aOutAsset)
{
}
