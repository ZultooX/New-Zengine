#include "NetworkDecoder.h"

MessageList NetworkDecoder::Decode(const NetData& someData)
{
	MessageList output;

	int size = 0;
	memcpy(&size, &someData.buffer[MESSAGE_SIZE_IDX], sizeof(int));

	for (int i = MESSAGE_START_IDX; i < size;)
	{
		char messageType = -1;
		memcpy(&messageType, &someData.buffer[i], sizeof(char));

		i += sizeof(char);

		if (messageType == (char)MessageType::SINGLE)
		{
			output.messages.push_back(DecodedMessage{});
			HandleSingle(someData, i, output.messages.back());
		}

		else if (messageType == (char)MessageType::BLOCK)
			output.blockMessages.push_back(HandleBlock(someData, i));
	}


	return output;
}

void NetworkDecoder::HandleSingle(const NetData& someData, int& aIdx, DecodedMessage& aOutMessage)
{
	memcpy(&aOutMessage.identifier, &someData.buffer[aIdx], sizeof(char));
	aIdx += sizeof(char);

	char size = 0;
	memcpy(&size, &someData.buffer[aIdx], sizeof(char));
	aIdx += sizeof(char);

	aOutMessage.message.resize(size);

	memcpy(&aOutMessage.message[0], &someData.buffer[aIdx], size);
	aIdx += size;
}

BlockMessage NetworkDecoder::HandleBlock(const NetData& someData, int& aIdx)
{
	BlockMessage output;

	int blockSize = 0;
	memcpy(&blockSize, &someData.buffer[aIdx], sizeof(int));


	aIdx += sizeof(int);

	memcpy(&output.owner, &someData.buffer[aIdx], sizeof(int));
	aIdx += sizeof(int);

	while (aIdx < blockSize)
	{
		output.messages.push_back(DecodedMessage{});
		HandleSingle(someData, aIdx, output.messages.back());
	}


	return output;
}
