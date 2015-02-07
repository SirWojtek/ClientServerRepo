#pragma once

#include <gmock/gmock.h>
#include <memory>

#include "IMessageQueue.hpp"
#include "NetworkMessage.hpp"

class MessageQueueMock : public IMessageQueue
{
	virtual void pushMessage(NetworkMessage&& a) { pushMessageProxy(a); }
	MOCK_METHOD1(pushMessageProxy, void(NetworkMessage));
	MOCK_METHOD1(pushMessage, void(const NetworkMessage& message));
	MOCK_METHOD0(popMessage, NetworkMessagePtr());
};
typedef std::shared_ptr<MessageQueueMock> MessageQueueMockPtr;
