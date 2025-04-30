#pragma once

#include <functional>
#include <NetworkCommon.h>

namespace Zengine::Networking
{
	class Client;
}
class NetworkManager final
{
public:
	void Init();
	void Update();

public:
	void ConnectToServer();
	void DisconnectFromServer();

	void SetRecieveMessageEvent();

	Zengine::Networking::Client* GetClient();

private:
	void ProcessMessages(const MessageList& someData);

private:
	Zengine::Networking::Client* Client;
};
