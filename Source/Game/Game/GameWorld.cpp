#include "GameWorld.h"

#include<Engine/ComponentSystem/GameObject.h>
#include<Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include<Engine/ComponentSystem/Components/TransformComponent.h>
#include<Engine/ComponentSystem/Components/Rendering/Camera/EditorCamera.h>

#include <Engine/AssetManagement/MaterialManager.h>

#include <Engine/Utilities/MainSingleton.h>


void GameWorld::Init()
{
	{
		CS::GameObject* obj = CS::GameObject::Create();
		obj->transform->eulerAngles.x = PI * 0.5F;
		obj->transform->eulerAngles.z = PI;

		CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
		rend->SetMesh(ZENGINE_MODELS_PATH"Reaper Anubis.fbx");

		{
			//Material* body = MainSingleton::GetInstance<MaterialManager>().Get("Assets/Materials/ReaperAnubis_Body.mat");
			//body->AddTexture("Albedo", ZENGINE_TEXTURES_PATH"TEX_Anubis_Reaper_a.tga", 0);
			//body->AddTexture("Normal", ZENGINE_TEXTURES_PATH"TEX_Anubis_Reaper_n.tga", 1);
			//body->AddTexture("Material", ZENGINE_TEXTURES_PATH"TEX_Anubis_Reaper_m.tga", 2);

			//body->GetShader().SetPixelShader(ZENGINE_SHADERS_PATH"PS_Default.cso");
			//body->GetShader().SetVertexShader(ZENGINE_SHADERS_PATH"VS_Default.cso");

			//body->Save();
			rend->AddMaterial("Assets/Materials/ReaperAnubis_Body.mat");
		}


		{
			//Material* head = MainSingleton::GetInstance<MaterialManager>().Get("Assets/Materials/ReaperAnubis_Head.mat");
			//head->AddTexture("Albedo", ZENGINE_TEXTURES_PATH"TEX_Anubis_Reaper_Head_a.tga", 0);
			//head->AddTexture("Normal", ZENGINE_TEXTURES_PATH"TEX_Anubis_Reaper_Head_n.tga", 1);
			//head->AddTexture("Material", ZENGINE_TEXTURES_PATH"TEX_Anubis_Reaper_Head_m.tga", 2);

			//head->GetShader().SetPixelShader(ZENGINE_SHADERS_PATH"PS_Default.cso");
			//head->GetShader().SetVertexShader(ZENGINE_SHADERS_PATH"VS_Default.cso");

			//head->Save();
			rend->AddMaterial("Assets/Materials/ReaperAnubis_Head.mat");
		}
	}

	//{
	//	CS::GameObject* obj = CS::GameObject::Create();
	//	obj->transform->eulerAngles.x = PI * 0.5F;
	//	obj->transform->eulerAngles.z = PI;
	//	obj->transform->position.x = -1.f;

	//	CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
	//	rend->SetMesh(ZENGINE_MODELS_PATH"Reaper OW1.fbx");

	//	rend->SetTexture(ZENGINE_TEXTURES_PATH"TEX_Regular_Reaper_a.tga", TextureSlot::Albedo);
	//	rend->SetTexture(ZENGINE_TEXTURES_PATH"TEX_Regular_Reaper_n.tga", TextureSlot::Normal);

	//	rend->SetPixelShader(ZENGINE_SHADERS_PATH"PS_Default.cso");
	//	rend->SetVertexShader(ZENGINE_SHADERS_PATH"VS_Default.cso");
	//}	
	//
	//{
	//	CS::GameObject* obj = CS::GameObject::Create();
	//	obj->transform->eulerAngles.x = PI * 0.5F;
	//	obj->transform->eulerAngles.z = PI;
	//	obj->transform->position.x = -5.f;

	//	CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
	//	rend->SetMesh(ZENGINE_MODELS_PATH"Genji Street Runner.fbx");

	//	rend->SetTexture(ZENGINE_TEXTURES_PATH"TEX_Genji_Street_a.tga", TextureSlot::Albedo);
	//	rend->SetTexture(ZENGINE_TEXTURES_PATH"TEX_Genji_Street_n.tga", TextureSlot::Normal);

	//	rend->SetPixelShader(ZENGINE_SHADERS_PATH"PS_Default.cso");
	//	rend->SetVertexShader(ZENGINE_SHADERS_PATH"VS_Default.cso");
	//}

	//{
	//	CS::GameObject* obj = CS::GameObject::Create();
	//	//obj->transform->eulerAngles.x = PI * 0.5F;
	//	obj->transform->eulerAngles.y = PI;
	//	obj->transform->position.x = 3.f;
	//	obj->transform->scale = Vector3f(0.01f, 0.01f, 0.01f);

	//	CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
	//	rend->SetMesh(ZENGINE_MODELS_PATH"Bro.fbx");

	//	rend->SetTexture(ZENGINE_TEXTURES_PATH"TGA_Bro_C.dds", TextureSlot::Albedo);

	//	rend->SetPixelShader(ZENGINE_SHADERS_PATH"PS_Default.cso");
	//	rend->SetVertexShader(ZENGINE_SHADERS_PATH"VS_Default.cso");
	//}

	//{
	//	CS::GameObject* obj = CS::GameObject::Create();
	//	//obj->transform->eulerAngles.x = PI * 0.5F;
	//	obj->transform->eulerAngles.y = PI;
	//	obj->transform->position.x = -3.f;
	//	obj->transform->scale = Vector3f(0.01f, 0.01f, 0.01f);

	//	CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
	//	rend->SetMesh(ZENGINE_MODELS_PATH"Shaman.fbx");

	//	rend->SetTexture(ZENGINE_TEXTURES_PATH"TEX_Shaman_a.dds", TextureSlot::Albedo);

	//	rend->SetPixelShader(ZENGINE_SHADERS_PATH"PS_Default.cso");
	//	rend->SetVertexShader(ZENGINE_SHADERS_PATH"VS_Default.cso");
	//}

	{
		CS::GameObject* obj = CS::GameObject::Create();
		obj->AddComponent<CS::EditorCamera>();
	}


	//MeshManager manager;
	//manager.Init();

	//Mesh* mesh = manager.Get(ZENGINE_MODELS_PATH"Cube.fbx");
	//mesh;
}

void GameWorld::Update()
{

}
