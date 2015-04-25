#include <thread>
#include <string>
#include <memory>
#include <utility>
#include <map>
#include <stdexcept>

#include "common/socketServices/IMessageQueue.hpp"
#include "common/socketServices/IMessageCommander.hpp"
#include "CommunicationService.hpp"
#include "common/utilities/Console.hpp"
#include "common/socketServices/ITcpSocket.hpp"

#include "common/messages/MessageUtilities.hpp"

using common::messagetype::MessageType;

std::string CommunicationService::host = "127.0.0.1";
std::string CommunicationService::port = "4001";
unsigned CommunicationService::waitingForResponseCount = 5;

void CommunicationService::startService()
{
    tcpSocket_->connect(host, port);
    tcpSocket_ = nullptr;
    readerThread_ = messageReader_->start();
    writerThread_ = messageWriter_->start();

    console_.info << "Service started";
}

common::OkResponse CommunicationService::putMessageInQueue(const common::UpdatePlayer& message)
{
    return putMessage(message);
}

common::OkResponse CommunicationService::putMessageInQueue(const common::Login& message)
{
    return putMessage(message);
}

template<typename MessageT>
common::OkResponse CommunicationService::putMessage(const MessageT& message)
{
    std::string json = common::getMessageJson<MessageT>(message);
    writerQueue_->pushMessage(json);
    console_.debug << "Message added to queue";

    return getResponse();
}

common::OkResponse CommunicationService::getResponse()
{
    std::shared_ptr<std::string> response;

    for (unsigned i = 0; i < waitingForResponseCount; i++)
    {
        response = getMessage(common::messagetype::OkResponse, true);
        console_.debug << "Waiting for UpdatePlayer response: " << i + 1;

        if (response != nullptr)
        {
            break;
        }
    }

    if (response == nullptr)
    {
        throw std::runtime_error("Server did not send OkResponse message");
    }

    console_.debug << "Response received";
    auto responcePtr = common::getMessage<common::OkResponse>(*response);

    if (responcePtr == nullptr)
    {
        throw std::runtime_error("Responce message conversion failed");
    }

    return *responcePtr;
}

std::shared_ptr<std::string> CommunicationService::getMessage(
    const MessageType& type, bool wait)
{
    // if (isMessageOfTypeAlreadyReceived(type))
    // {
    //     return getMessageOfTypeAlreadyReceived(type);
    // }

    // return wait ? getMessageOfTypeNotReceived(type) : nullptr;
    return getMessageOfTypeNotReceived(type);
}

void CommunicationService::tearDown()
{
    if (readerThread_ && readerThread_->joinable())
    {
        messageReader_->stop();
        readerThread_->join();
        console_.info << "Reader thread joined";
    }

    if (writerThread_ && writerThread_->joinable())
    {
        sendLogoutMessage();
        writerQueue_->waitForEmptyQueue();
        messageWriter_->stop();
        writerThread_->join();
        console_.info << "Writer thread joined";
    }

    console_.info << "Service ended";
}

void CommunicationService::sendLogoutMessage()
{
    using namespace common;

    Logout logoutMessage;
    std::string json = common::getMessageJson(logoutMessage);
    writerQueue_->pushMessage(json);

    getMessage(messagetype::OkResponse, true);
}

bool CommunicationService::isMessageOfTypeAlreadyReceived(const MessageType& type)
{
    return receivedMessages_.count(type) != 0;
}

std::shared_ptr<std::string> CommunicationService::getMessageOfTypeAlreadyReceived(
    const MessageType& type)
{
    auto messageIt = receivedMessages_.find(type);


    if (messageIt == receivedMessages_.end())
    {
        throw std::runtime_error("Message of given type doesn't exist in multimap");
    }

    std::shared_ptr<std::string> message = messageIt->second;
    receivedMessages_.erase(messageIt);
    return message;
}

std::shared_ptr<std::string> CommunicationService::getMessageOfTypeNotReceived(
    const MessageType& type)
{
    std::shared_ptr<std::string> message;

    while ((message = readerQueue_->popMessage()))
    {
        MessageType receivedMessageType = common::getMessageType(*message);

        if (receivedMessageType == type)
        {
            return message;
        }
        else
        {
            receivedMessages_.insert(
                std::pair<MessageType, std::shared_ptr<std::string>>(receivedMessageType, message));
            console_.info << "Message multimap size: " << receivedMessages_.size();
        }
    }

    return nullptr;
}