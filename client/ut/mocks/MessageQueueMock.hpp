#ifndef MESSAGEQUEUE_MOCK_HPP_
#define MESSAGEQUEUE_MOCK_HPP_

#include <memory>
#include <string>
#include <gmock/gmock.h>


#include "common/socketServices/IMessageQueue.hpp"

class MessageQueueMock : public IMessageQueue
{
public:
    MOCK_METHOD1(pushMessage, void(const std::string& message));
    MOCK_METHOD0(popMessage, std::shared_ptr<std::string>());
    MOCK_METHOD0(waitForEmptyQueue, void());
};
typedef std::shared_ptr<MessageQueueMock> MessageQueueMockPtr;

#endif  // MESSAGEQUEUE_MOCK_HPP_
