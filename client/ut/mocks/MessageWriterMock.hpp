#pragma once

#include <gmock/gmock.h>
#include <memory>
#include <thread>

#include "IMessageWriter.hpp"

class MessageWriterMock : public IMessageWriter
{
public:
	MOCK_METHOD0(start, ThreadPtr());
};
typedef std::shared_ptr<MessageWriterMock> MessageWriterMockPtr;