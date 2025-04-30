#pragma once

#include <../../NetworkShared/NetworkShared/NetworkCommon.h>
#include <functional>

class Encoder;

namespace Zengine::Networking
{
	class Client final
	{
	public:
		Client() = default;

		void Update();

		void Connect();
		void Disconnect();

		const bool& RecievedMessage();
		const MessageList& GetList();

		void SetRecieveMessageEvent(std::function<void(const MessageList&)> aEvent);
		Encoder* GetEncoder();

	private:
		void ProcessMessages(const NetData& someData);
		void SendToServer(const NetData& someData);

		const bool& IsRunning() ;

	private:
		Encoder* myEncoder;

	private:
		bool myIsRunning = false;
		bool myRecievedMessage = false;

		MessageList myMessageList;

		std::function<void(const MessageList&)> myEvent;
	};
}