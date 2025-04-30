#pragma once

#include <string>

#include "NetworkCommon.h"

class Encoder final
{
public:
	Encoder() = default;

	// Begins a block message.
	void Begin(const int& aID);

	// Ends a block message.
	void End();

	const NetData& GetData();

public:
	template<typename T> void Write(const char& anIdentifier, const T aMessage);

	template<> void Write(const char& anIdentifier, const char* aMessage);
	template<> void Write(const char& anIdentifier, const std::string& aMessage);

private:
	void WriteBytes(const void* someData, const int& aSize);

private:
	NetData myData;
	int myCurrentBlockSize = 0;
	int myCurrentBlockSizeIdx = -1;
	int myCurrentIdx = MESSAGE_START_IDX;
	int mySize = MESSAGE_START_IDX;
	bool myBlockWasStarted = false;
};

template<typename T>
inline void Encoder::Write(const char& anIdentifier, const T aMessage)
{
	if (!myBlockWasStarted)
	{
		MessageType type = MessageType::SINGLE;
		WriteBytes(&type, sizeof(char));
	}

	const int size = sizeof(T);

	WriteBytes(&anIdentifier, sizeof(char));
	WriteBytes(&size, sizeof(char));
	WriteBytes(&aMessage, size);
}

template<>
inline void Encoder::Write(const char& anIdentifier, const char* aMessage)
{
	if (!myBlockWasStarted)
	{
		MessageType type = MessageType::SINGLE;
		WriteBytes(&type, sizeof(char));
	}

	const int size = strlen(aMessage);
	WriteBytes(&anIdentifier, sizeof(char));
	WriteBytes(&size, sizeof(char));
	WriteBytes(aMessage, size);
}

template<>
inline void Encoder::Write(const char& anIdentifier, const std::string& aMessage)
{
	if (!myBlockWasStarted)
	{
		MessageType type = MessageType::SINGLE;
		WriteBytes(&type, sizeof(char));
	}

	const int size = aMessage.size();
	WriteBytes(&anIdentifier, sizeof(char));
	WriteBytes(&size, sizeof(char));
	WriteBytes(aMessage.c_str(), size);
}
