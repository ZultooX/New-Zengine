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
		//CS::GameObject* obj = CS::GameObject::Create();
		//obj->transform->GetEulerAngles().x = PI * 0.5F;
		//obj->transform->GetEulerAngles().z = PI;
		//obj->transform->GetPosition().x = 0.75f;

		//obj->SetName("Reaper");

		//CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
		//rend->SetMesh(ZENGINE_MODELS_PATH"Reaper Anubis.fbx");

		//rend->AddMaterial("Assets/Materials/ReaperAnubis_Body.mat");
		//rend->AddMaterial("Assets/Materials/ReaperAnubis_Head.mat");
		 
		//obj->AddComponent<CS::NetworkSyncer>();
	}

	{
		CS::GameObject* obj = CS::GameObject::Create();
		obj->transform->SetEulerAngles(Vector3f(PI * 0.5F, 0.f, PI));
		obj->transform->SetPosition(Vector3f(-0.75f, 0.f, 0.f));


		obj->SetName("Genji");

		CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
		rend->SetMesh(ZENGINE_MODELS_PATH"Divine monkey.fbx");

		rend->AddMaterial("Assets/Materials/Monkey.mat");
		rend->AddMaterial("Assets/Materials/Monkey.mat");
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
