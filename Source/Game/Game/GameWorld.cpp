#include "GameWorld.h"

#include<Engine/ComponentSystem/GameObject.h>
#include<Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include<Engine/ComponentSystem/Components/TransformComponent.h>
#include<Engine/ComponentSystem/Components/Rendering/Camera/EditorCamera.h>
#include<Engine/ComponentSystem/Components/Networking/NetworkSyncerComponent.h>

#include <Engine/Utilities/MainSingleton.h>


void GameWorld::Init()
{
	{
		CS::GameObject* obj = CS::GameObject::Create();
		obj->AddComponent<CS::EditorCamera>();

		obj->SetName("Editor Camera");

		obj->transform->SetPosition(Vector3f(0.19f, 0.67f, -2.8f));
	}
}

void GameWorld::Update()
{

}
