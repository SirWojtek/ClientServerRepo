#include <thread>
#include <string>
#include <memory>
#include <utility>
#include <map>
#include <stdexcept>

#include "IMessageQueue.hpp"
#include "IMessageCommander.hpp"
#include "CommunicationService.hpp"
#include "common/utilities/Console.hpp"
#include "ITcpSocket.hpp"

#include "common/messages/UpdateEnvironment.hpp"
#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageUtilities.hpp"

using common::messagetype::MessageType;

void CommunicationService::startService(
    const std::string& host, const std::string& port)
{
    tcpSocket_->connect(host, port);
    tcpSocket_ = nullptr;
    readerThread_ = messageReader_->start();
    writerThread_ = messageWriter_->start();
}

void CommunicationService::putMessageInQueue(const common::UpdatePlayer& message)
{
    std::string json = common::getMessageJson<common::UpdatePlayer>(message);
    writerQueue_->pushMessage(json);
    console_.info << "Message added to queue";
}

std::shared_ptr<std::string> CommunicationService::getMessage(
    const MessageType& type)
{
    if (isMessageOfTypeAlreadyReceived(type))
    {
        return getMessageOfTypeAlreadyReceived(type);
    }

    return getMessageOfTypeNotReceived(type);
}

void CommunicationService::tearDown()
{
    if (readerThread_->joinable())
    {
        messageReader_->stop();
        readerThread_->join();
        console_.debug << "Reader thread joined";
    }

    if (writerThread_->joinable())
    {
        writerQueue_->waitForEmptyQueue();
        messageWriter_->stop();
        writerThread_->join();
        console_.debug << "Writer thread joined";
    }

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

    return messageIt->second;
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
        }
    }

    return nullptr;
}
