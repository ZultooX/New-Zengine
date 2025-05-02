#include "NetworkEncoder.h"

void Encoder::Clear()
{
	mySize = 0;
	myCurrentBlockSize = 0;
	myCurrentBlockSizeIdx = 0;
	myCurrentIdx = MESSAGE_START_IDX;

	for (int i = 0; i < MAX_MESSAGE_SIZE; i++)
	{
		myData.buffer[i] = -52;
	}
}

void Encoder::Begin(const int& aID)
{
	MessageType type = MessageType::BLOCK;
	WriteBytes(&type, sizeof(char));

	myCurrentBlockSizeIdx = myCurrentIdx;
	myCurrentIdx += sizeof(int);
	mySize += sizeof(int);

	WriteBytes(&aID, sizeof(int));

	myCurrentBlockSize += sizeof(int);
	myBlockWasStarted = true;
}

void Encoder::End()
{
	memcpy(&myData.buffer[myCurrentBlockSizeIdx], &myCurrentBlockSize, sizeof(int));
	myCurrentBlockSize = 0;
	myCurrentBlockSizeIdx = 0;

	myBlockWasStarted = false;
}

const NetData& Encoder::GetData()
{
	myCurrentIdx = MESSAGE_START_IDX;
	memcpy(&myData.buffer[MESSAGE_SIZE_IDX], &mySize, sizeof(int));
	mySize = MAX_MESSAGE_SIZE;
	return myData;
}

void Encoder::WriteBytes(const void* someData, const int& aSize)
{
	memcpy(&myData.buffer[myCurrentIdx], someData, aSize);
	myCurrentIdx += aSize;
	myCurrentBlockSize += aSize;
	mySize += aSize;
}
