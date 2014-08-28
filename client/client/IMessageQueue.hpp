#pragma once

#include <string>
#include <memory>

#include "NetworkMessage.hpp"

class IMessageQueue
{
public:
	virtual ~IMessageQueue() {}
	virtual void pushMessage(NetworkMessage&& message) = 0;
	virtual void pushMessage(const NetworkMessage& message) = 0;
	virtual NetworkMessagePtr popMessage() = 0;
};
typedef std::shared_ptr<IMessageQueue> MessageQueuePtr;
