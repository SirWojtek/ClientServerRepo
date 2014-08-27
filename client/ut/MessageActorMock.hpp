#pragma once

#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "IMessageWriter.hpp"

class MessageActorMock : public IMessageWriter
{
public:
	MOCK_METHOD1(asyncSend, void(std::shared_ptr<std::string>));
	MOCK_METHOD0(asyncGet, bool());
};
typedef std::shared_ptr<MessageActorMock> MessageActorMockPtr;