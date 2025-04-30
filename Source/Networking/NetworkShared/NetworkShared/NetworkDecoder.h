#pragma once

#include <vector>

#include "NetworkCommon.h"

class NetworkDecoder
{
public:
	MessageList Decode(const NetData& someData);

private:
	void HandleSingle(const NetData& someData, int& aIdx, DecodedMessage& aOutMessage);
	BlockMessage HandleBlock(const NetData& someData, int& aIdx);
};

