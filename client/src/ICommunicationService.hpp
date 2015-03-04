#ifndef ICOMMUNICATION_SERVICE_HPP_
#define ICOMMUNICATION_SERVICE_HPP_

#include <memory>
#include <thread>
#include <string>

#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/OkResponse.hpp"
#include "common/messages/MessageTypes.hpp"

class ICommunicationService
{
public:
    virtual ~ICommunicationService() {}
    virtual void startService() = 0;
    virtual common::OkResponse putMessageInQueue(const common::UpdatePlayer& message) = 0;
    virtual std::shared_ptr<std::string> getMessage(
        const common::messagetype::MessageType& type, bool wait) = 0;
    virtual void tearDown() = 0;
};
using CommunicationServicePtr = std::shared_ptr<ICommunicationService>;

#endif  // ICOMMUNICATION_SERVICE_HPP_
