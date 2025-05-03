#include "GameWorld.h"

#include<Engine/ComponentSystem/GameObject.h>
#include<Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include<Engine/ComponentSystem/Components/TransformComponent.h>
#include<Engine/ComponentSystem/Components/Rendering/Camera/EditorCamera.h>
#include<Engine/ComponentSystem/Components/Networking/NetworkSyncerComponent.h>

#include <Engine/AssetManagement/MaterialManager.h>

#include <Engine/Utilities/MainSingleton.h>


void GameWorld::Init()
{
	{
		CS::GameObject* obj = CS::GameObject::Create();
		obj->transform->SetEulerAngles(Vector3f(PI * 0.5F, 0.f, PI));
		obj->transform->SetPosition(Vector3f(1.75f, 0.f, 0.f));

		obj->SetName("Reaper");

		CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
		rend->SetMesh(ZENGINE_MODELS_PATH"Reaper Anubis.fbx");

		rend->AddMaterial("Assets/Materials/ReaperAnubis_Body.mat");
		rend->AddMaterial("Assets/Materials/ReaperAnubis_Head.mat");
	}

	{ // Shaman
		CS::GameObject* obj = CS::GameObject::Create();
		obj->transform->SetScale(Vector3f(0.01f, 0.01f, 0.01f));
		obj->transform->SetPosition(Vector3f(-0.75f, 0.f, 0.f));


		obj->SetName("Shaman");

		CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
		rend->SetMesh(ZENGINE_MODELS_PATH"Shaman.fbx");

		rend->AddMaterial("Assets/Materials/Shaman.mat");
	}

	{ // Bro
		CS::GameObject* obj = CS::GameObject::Create();
		obj->transform->SetScale(Vector3f(0.01f, 0.01f, 0.01f));
		obj->transform->SetPosition(Vector3f(0.75f, 0.f, 0.f));


		obj->SetName("Bro");

		CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
		rend->SetMesh(ZENGINE_MODELS_PATH"Bro.fbx");

		rend->AddMaterial("Assets/Materials/TgaBro.mat");
	}


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
