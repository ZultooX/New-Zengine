#pragma once

#include "WinSock2.h"

#pragma comment(lib, "Ws2_32.lib")
#include <vector>

#include <NetworkCommon.h>

namespace Zengine::Networking
{
	class Server final
	{
	public:
		void Startup();
		void Update();

		void SendToClients(const NetData& aMessage, sockaddr_in& sender);

	public:
		const bool& IsRunning();

	private:
		bool myIsRunning = false;

		NetData myMessageBuffer;

		std::vector<sockaddr_in> myConnectedClients;
		std::vector<int> myIds;

		SOCKET mySocket;
		sockaddr_in myAddress;
		fd_set myMasterSet;
	};
}