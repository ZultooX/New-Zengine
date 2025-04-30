#pragma once

#include <array>
#include <vector>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 42000

#define MESSAGE_SIZE_IDX 0
#define MESSAGE_START_IDX 4
#define MAX_MESSAGE_SIZE 1024

enum MessageIdentifier : char
{
	CLIENT_CONNECTED,
	CLIENT_DISCONNECTED,

	SpawnPlayer,
	Transform,
};

enum class MessageType {
	BLOCK,
	SINGLE
};

struct NetData
{
	char buffer[MAX_MESSAGE_SIZE];
};

// TODO: MALLOC GER HEAP CORRUPTION.



struct DecodedMessage
{
	~DecodedMessage()
	{
	}

	int identifier;
	std::vector<char> message;
};


struct BlockMessage
{
	int owner;
	std::vector<DecodedMessage> messages;
};

struct MessageList
{
	std::vector<DecodedMessage> messages;
	std::vector<BlockMessage> blockMessages;
};