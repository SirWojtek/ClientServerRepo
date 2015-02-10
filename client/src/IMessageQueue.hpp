#ifndef IMESSAGE_QUEUE_HPP_
#define IMESSAGE_QUEUE_HPP_

#include <string>
#include <memory>

class IMessageQueue
{
public:
    virtual ~IMessageQueue() {}
	virtual void pushMessage(const std::string& message) = 0;
	virtual std::string popMessage() = 0;
};
typedef std::shared_ptr<IMessageQueue> MessageQueuePtr;

#endif  // IMESSAGE_QUEUE_HPP_
