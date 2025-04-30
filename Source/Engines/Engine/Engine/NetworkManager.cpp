#include "NetworkManager.h"

#include <Client.h>

void NetworkManager::Init()
{
	Client = new Zengine::Networking::Client();
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
	Client->SetRecieveMessageEvent([this](const MessageList& someData) {  ProcessMessages(someData); });
}

Zengine::Networking::Client* NetworkManager::GetClient() { return Client; }

void NetworkManager::ProcessMessages(const MessageList& someData)
{
	for (const BlockMessage& block : someData.blockMessages)
	{
		for (const DecodedMessage& message : block.messages)
		{
			switch (message.identifier)
			{
			case MessageIdentifier::Transform:
			{

			}break;

			default:
				break;
			}
		}
	}
}
