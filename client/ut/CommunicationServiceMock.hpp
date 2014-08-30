#pragma once

#include <gmock/gmock.h>
#include <memory>

#include "ICommunicationService.hpp"

class CommunicationServiceMock : public ICommunicationService
{
public:
	virtual void putMessageInQueue(NetworkMessage&& message) { putMessageInQueueProxy(message); }
	MOCK_METHOD2(startService, void(const std::string& host, const std::string& port));
	MOCK_METHOD1(putMessageInQueue, void(const NetworkMessage& message));
	MOCK_METHOD1(putMessageInQueueProxy, void(NetworkMessage message));
	MOCK_METHOD0(tearDown, void());
};
typedef std::shared_ptr<CommunicationServiceMock> CommunicationServiceMockPtr;
