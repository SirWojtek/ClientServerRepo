#ifndef MESSAGE_QUEUE_STUB_HPP_
#define MESSAGE_QUEUE_STUB_HPP_

#include "common/socketServices/IMessageQueue.hpp"

struct MessageQueueStub : public IMessageQueue
{
    void pushMessage(const std::string& message) override
    {
        pushedMessage = message;
    }
    std::shared_ptr<std::string> popMessage() override
    {
        return messageToPop;
    }
    void waitForEmptyQueue() override {}
    void waitForEmptyQueueWithTimeout() override {}

    std::shared_ptr<std::string> messageToPop;
    std::string pushedMessage;
};

#endif  // MESSAGE_QUEUE_STUB_HPP_
