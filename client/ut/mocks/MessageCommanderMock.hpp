#ifndef MESSAGE_COMMANDER_MOCK_HPP_
#define MESSAGE_COMMANDER_MOCK_HPP_

#include <gmock/gmock.h>
#include <memory>
#include <thread>

#include "common/socketServices/IMessageCommander.hpp"

class MessageCommanderMock : public IMessageCommander
{
public:
    MOCK_METHOD0(start, ThreadPtr());
};
using MessageCommanderMockPtr = std::shared_ptr<MessageCommanderMock>;

#endif  // MESSAGE_COMMANDER_MOCK_HPP_
