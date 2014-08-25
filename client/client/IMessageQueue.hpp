#pragma once

#include <string>
#include <memory>

class IMessageQueue
{
public:
	virtual ~IMessageQueue() {}
	virtual void pushMessage(std::string&& message) = 0;
	virtual std::shared_ptr<std::string> popMessage() = 0;
};
typedef std::shared_ptr<IMessageQueue> MessageQueuePtr;
