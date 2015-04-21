#ifndef COMMUNICATION_SERVICE_SUT_BUILDER_HPP_
#define COMMUNICATION_SERVICE_SUT_BUILDER_HPP_

#include <memory>

#include "client/ut/stubs/MessageCommanderStub.hpp"
#include "client/ut/stubs/MessageQueueStub.hpp"
#include "client/ut/stubs/TcpSocketStub.hpp"

#include "client/src/CommunicationService.hpp"

struct CommunicationServiceSut
{
    CommunicationServicePtr communicationServ;
    MessageQueuePtr messageQueue;
};

CommunicationServiceSut buildCommunicationServiceSut()
{
    auto messageQueue = std::make_shared<MessageQueueStub>();
    auto messageCommander = std::make_shared<MessageCommanderStub>();

    return {std::make_shared<CommunicationService>(std::make_shared<TcpSocketStub>(),
        messageQueue, messageCommander, messageQueue, messageCommander), messageQueue};
}

#endif  // COMMUNICATION_SERVICE_SUT_BUILDER_HPP_
