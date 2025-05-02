#include "Client.h"

#include <WinSock2.h>
#include "WS2tcpip.h"

#include <NetworkCommon.h>

#include <NetworkEncoder.h>
#include <NetworkDecoder.h>

namespace {
	SOCKET udpSocket;
	WSADATA winsockData;
	sockaddr_in addrServer{};
	NetData messageBuffer;
	fd_set serverSet;

	NetworkDecoder decoder;
}


namespace Zengine::Networking
{
	void Client::Update()
	{
		if (!myIsRunning) return;

		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(udpSocket, &readfds);

		sockaddr_in clientSocket;
		int clientSize = sizeof(clientSocket);


		timeval timeout = { 0, 10000 };

		if (select(0, &readfds, nullptr, nullptr, &timeout) > 0)
		{
			int size = recvfrom(udpSocket, messageBuffer.buffer, MAX_MESSAGE_SIZE, 0, (sockaddr*)&clientSocket, &clientSize);
			if (size > 0)
			{
				ProcessMessages(messageBuffer);
			}
		}

		SendToServer(myEncoder->GetData());
	}

	void Client::Connect()
	{
		if (WSAStartup(MAKEWORD(2, 2), &winsockData) != 0) return;

		udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (udpSocket == INVALID_SOCKET) return;


		u_long iMode = true;
		ioctlsocket(udpSocket, FIONBIO, &iMode);

		addrServer.sin_family = AF_INET;

		InetPton(AF_INET, TEXT(SERVER_ADDRESS), &addrServer.sin_addr.s_addr);

		addrServer.sin_port = htons(SERVER_PORT);

		myEncoder = new Encoder;
		myEncoder->Write(CLIENT_CONNECTED, 0);

		SendToServer(myEncoder->GetData());

		myIsRunning = true;
	}

	void Client::Disconnect()
	{
		myEncoder->Write(CLIENT_DISCONNECTED, 0);

		SendToServer(myEncoder->GetData());
	}

	const bool& Client::RecievedMessage() { return myRecievedMessage; }

	const MessageList& Client::GetList()
	{
		myRecievedMessage = false;
		return myMessageList;
	}

	void Client::SetRecieveMessageEvent(std::function<void(const MessageList&)> aEvent)
	{
		myEvent = aEvent;
	}

	void Client::ProcessMessages(const NetData& someData)
	{
		myRecievedMessage = true;
		myMessageList = decoder.Decode(someData);
		myEvent(myMessageList);
	}

	void Client::SendToServer(const NetData& someData)
	{
		sendto(udpSocket, someData.buffer, sizeof(someData.buffer), 0, reinterpret_cast<sockaddr*>(&addrServer), sizeof(addrServer));
		myEncoder->Clear();
	}

	Encoder* Client::GetEncoder() { return myEncoder; }
	const bool& Client::IsRunning() const { return myIsRunning; }
}