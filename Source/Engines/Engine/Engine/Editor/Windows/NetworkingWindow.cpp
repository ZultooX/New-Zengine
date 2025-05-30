#include "NetworkingWindow.h"

#include <Zultools/Random.h>
#include <ImGui/imgui.h>
#include <Engine/Editor/DebugLogger.h>
#include <Engine/Engine.h>
#include <Client.h>

#include <Engine/ComponentSystem/Components/Networking/NetworkSyncerComponent.h>
#include <Engine/ComponentSystem/Components/Rendering/MeshRendererComponent.h>
#include <Engine/ComponentSystem/Components/TransformComponent.h>
#include <Engine/ComponentSystem/GameObject.h>
#include <NetworkCommon.h>
#include <NetworkEncoder.h>

NetworkingWindow::NetworkingWindow(const int& aId)
{
	myWindowName = "Networking";
	myID = aId == -1 ? Random::GetValue<int>() : aId;
}

void NetworkingWindow::Open()
{
}

void NetworkingWindow::Update()
{
	if (!myIsConnected && ImGui::Button("Connect")) ConnectToServer();
	else if (myIsConnected && ImGui::Button("Disconnect")) DisconnectToServer();


	else if (myIsConnected && ImGui::Button("Spawn Player"))
	{
		CS::GameObject* obj = CS::GameObject::Create();
		obj->transform->SetEulerAngles(Vector3f(PI * 0.5F, 0.f, PI));
		obj->transform->SetPosition(Vector3f(0.75f, 0.f, 0.f));


		obj->SetName("Reaper");

		CS::MeshRenderer* rend = obj->AddComponent<CS::MeshRenderer>();
		rend->SetMesh(ZENGINE_MODELS_PATH"Reaper Anubis.fbx");

		rend->AddMaterial("Assets/Materials/ReaperAnubis_Body.mat");
		rend->AddMaterial("Assets/Materials/ReaperAnubis_Head.mat");

		obj->AddComponent<CS::NetworkSyncer>();

		Encoder* encoder = Engine::GetNetworkManager().GetClient()->GetEncoder();
		encoder->Write(MessageIdentifier::SpawnPlayer, obj->GetID());
	}
}

void NetworkingWindow::Close()
{
}



void NetworkingWindow::ConnectToServer()
{
	myIsConnected = true;

	Engine::GetNetworkManager().ConnectToServer();

	DebugLogger::Log("Connecting to server.");
}

void NetworkingWindow::DisconnectToServer()
{
	myIsConnected = false;

	Engine::GetNetworkManager().DisconnectFromServer();

	DebugLogger::Log("Disconnecting from server.");
}
