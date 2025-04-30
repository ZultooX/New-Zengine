#include "Server.h"

#include <iostream>
#include <NetworkDecoder.h>

namespace Zengine::Networking
{
	bool operator==(const sockaddr_in& lhs, const sockaddr_in& rhs)
	{
		return (lhs.sin_addr.s_addr == rhs.sin_addr.s_addr && lhs.sin_port == rhs.sin_port && lhs.sin_family == rhs.sin_family);
	}

	void Server::Startup()
	{
		WSADATA data;

		{ // Starting winsock
			std::cout << "Starting winsock.....   ";
			if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
			{
				std::cout << ("\nWSA setup failed:\n" + WSAGetLastError());
				return;
			}
			std::cout << "Succeded!" << std::endl;
		}


		{ // Creating socket
			std::cout << "Creating socket.....   ";
			mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (mySocket == INVALID_SOCKET)
			{
				std::cout << ("\nSocket creation failed. \n" + WSAGetLastError());
				return;
			}
			std::cout << "Succeded!" << std::endl;
		}


		{ //Bind socket.
			myAddress.sin_family = AF_INET;
			myAddress.sin_addr.s_addr = INADDR_ANY;
			myAddress.sin_port = htons(42000);

			std::cout << "Binding socket.....   ";
			if (bind(mySocket, reinterpret_cast<sockaddr*>(&myAddress), sizeof(myAddress)) == SOCKET_ERROR)
			{
				std::cout << ("\nSocket couldnt be bound. \n" + WSAGetLastError());
				return;
			}
			std::cout << "Succeded!" << std::endl;
		}

		myIsRunning = true;

		system("cls");
		std::cout << ("Server started succesfully!") << std::endl;
	}

	void Server::Update()
	{
		ZeroMemory(myMessageBuffer.buffer, MAX_MESSAGE_SIZE);

		FD_ZERO(&myMasterSet);
		FD_SET(mySocket, &myMasterSet);

		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;

		int ready = select(0, &myMasterSet, nullptr, nullptr, &timeout);
		if (ready == SOCKET_ERROR)
		{
			myIsRunning = false;
			std::cout << ("\nSelect");
			return;
		}

		if (ready == 0) return;
		sockaddr_in clientSocket;
		int clientSize = sizeof(clientSocket);
		const int message = recvfrom(mySocket, myMessageBuffer.buffer, MAX_MESSAGE_SIZE, 0, (sockaddr*)&clientSocket, &clientSize);


		NetworkDecoder decoder;
		MessageList list = decoder.Decode(myMessageBuffer);

		for (DecodedMessage& message : list.messages)
		{
			if (message.identifier == CLIENT_CONNECTED)
			{
				std::cout << "Client connected!" << std::endl;
				myConnectedClients.push_back(clientSocket);
				break;
			}

			else if (message.identifier == CLIENT_DISCONNECTED)
			{
				for (int i = 0; i < (int)myConnectedClients.size(); i++)
				{
					if (myConnectedClients[i] == clientSocket)
					{
						std::cout << "Client disconnected!" << std::endl;
						myConnectedClients.erase(myConnectedClients.begin() + i);
						break;
					}
				}
				break;
			}
		}

		SendToClients(myMessageBuffer, clientSocket);
	}

	void Server::SendToClients(const NetData& aMessage, sockaddr_in& sender)
	{
		for (auto client : myConnectedClients)
		{
			if (client == sender) continue;

			sendto(mySocket, aMessage.buffer, sizeof(aMessage.buffer), 0, reinterpret_cast<sockaddr*>(&client), sizeof(client));
		}
	}

	const bool& Server::IsRunning() { return myIsRunning; }
}