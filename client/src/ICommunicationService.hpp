#ifndef ICOMMUNICATION_SERVICE_HPP_
#define ICOMMUNICATION_SERVICE_HPP_

#include <memory>
#include <thread>
#include <string>

#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageTypes.hpp"

class ICommunicationService
{
public:
    virtual ~ICommunicationService() {}
    virtual void startService(const std::string& host,
        const std::string& port) = 0;
    virtual void putMessageInQueue(const common::UpdatePlayer& message) = 0;
    virtual std::shared_ptr<std::string> getMessage(
        const common::messagetype::MessageType& type) = 0;
    virtual void tearDown() = 0;
};
typedef std::shared_ptr<ICommunicationService> CommunicationServicePtr;

#endif  // ICOMMUNICATION_SERVICE_HPP_
