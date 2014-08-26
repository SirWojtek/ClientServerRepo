#pragma once

#include <gmock/gmock.h>
#include <memory>

#include "IMessageQueue.hpp"

class MessageQueueMock : public IMessageQueue
{
	virtual void pushMessage(std::string&& a) { pushMessageProxy(a); }
	MOCK_METHOD1(pushMessageProxy, void(std::string));
	MOCK_METHOD0(popMessage, std::shared_ptr<std::string>());
};
typedef std::shared_ptr<MessageQueueMock> MessageQueueMockPtr;
