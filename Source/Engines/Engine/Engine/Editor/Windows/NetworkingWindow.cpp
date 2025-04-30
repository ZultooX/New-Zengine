#include "NetworkingWindow.h"

#include <Zultools/Random.h>
#include <ImGui/imgui.h>
#include <Engine/Editor/DebugLogger.h>
#include <Engine/Engine.h>
#include <Client.h>

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
