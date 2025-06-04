#include "NetworkManager.h"

#include <Client.h>
#include <Engine/ComponentSystem/Components/Networking/NetworkSyncerComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/GameObject.h>

void NetworkManager::Init()
{
	Client = new Zengine::Networking::Client();
	Client->SetRecieveMessageEvent([this](const MessageList& someData) {  ProcessMessages(someData); });
}

void NetworkManager::Update()
{
	Client->Update();
}

void NetworkManager::ConnectToServer()
{
	Client->Connect();
}

void NetworkManager::DisconnectFromServer()
{
	Client->Disconnect();
}

void NetworkManager::SetRecieveMessageEvent()
{
	
}

Zengine::Networking::Client* NetworkManager::GetClient() { return Client; }

#include <Engine/ComponentSystem/GameObject.h>
#include <Engine/ComponentSystem/GameObjectManager.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/Editor/DebugLogger.h>

void To(const DecodedMessage& message, const BlockMessage* block)
{
	//switch (message.identifier)
	//{
	//case MessageIdentifier::CLIENT_CONNECTED:
	//{
	//	DebugLogger::LogError("Client joined!");
	//}break;

	//case MessageIdentifier::CLIENT_DISCONNECTED:
	//{
	//	DebugLogger::LogError("Disconnected!");
	//}break;

	//case MessageIdentifier::SpawnPlayer:
	//{
	//	int id = 0;
	//	memcpy(&id, message.message.data(), sizeof(int));

	//	CS::GameObject* obj = CS::GameObject::Create(id);
	//	obj->transform->SetEulerAngles(Vector3f(PI * 0.5F, 0.f, PI));
	//	obj->transform->SetPosition(Vector3f(0.75f, 0.f, 0.f));

	//	obj->SetName("Reaper");

	//	CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
	//	rend->SetMesh(ZENGINE_MODELS_PATH"Reaper Anubis.fbx");

	//	rend->AddMaterial("Assets/Materials/ReaperAnubis_Body.mat");
	//	rend->AddMaterial("Assets/Materials/ReaperAnubis_Head.mat");
	//}break;

	//case MessageIdentifier::Transform:
	//{
	//	Zengine::ComponentSystem::GameObject* obj = Zengine::ComponentSystem::GameObjectManager::GetGameObject(block->owner);
	//	if (obj == nullptr) return;

	//	Datas::TransformData data = {};

	//	memcpy(&data, message.message.data(), sizeof(Datas::TransformData));

	//	obj->transform->SetPosition(data.pos);
	//	obj->transform->SetEulerAngles(data.eulerAngles);
	//	obj->transform->SetScale(data.scale);
	//}break;

	//default:
	//	break;
	//}
}

void NetworkManager::ProcessMessages(const MessageList& someData)
{
	for (const BlockMessage& block : someData.blockMessages)
	{
		for (const DecodedMessage& message : block.messages)
		{
			To(message, &block);
		}
	}

	for (const DecodedMessage& message : someData.messages)
	{
		To(message, nullptr);
	}
}
