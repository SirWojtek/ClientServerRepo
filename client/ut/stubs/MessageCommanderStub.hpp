#ifndef MESSAGE_COMMANDER_STUB_HPP_
#define MESSAGE_COMMANDER_STUB_HPP_

#include "common/socketServices/IMessageCommander.hpp"

struct MessageCommanderStub : public IMessageCommander
{
    ThreadPtr start() override
    {
        return nullptr;
    }
};

#endif  // MESSAGE_COMMANDER_STUB_HPP_
