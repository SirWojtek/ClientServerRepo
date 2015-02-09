#include <thread>
#include <string>
#include <memory>

#include "IMessageQueue.hpp"
#include "CommunicationService.hpp"
#include "NetworkMessage.hpp"

void CommunicationService::startService(
    const std::string& host, const std::string& port)
{
    tcpSocket_->connect(host, port);
    tcpSocket_ = nullptr;
    writerThread_ = messageWriter_->start();
    readerThread_ = messageReader_->start();
}

void CommunicationService::putMessageInQueue(NetworkMessage&& message)
{
    writerQueue_->pushMessage(std::move(message));
    console_.info << "Message added to queue";
}

void CommunicationService::putMessageInQueue(const NetworkMessage& message)
{
    writerQueue_->pushMessage(message);
    console_.info << "Message added to queue";
}

// TODO: receiveMessage(messageType)

void CommunicationService::tearDown()
{
    if (writerThread_->joinable())
    {
        messageWriter_->stop();
        writerThread_->join();
    }

    if (readerThread_->joinable())
    {
        messageReader_->stop();
        readerThread_->join();
    }
}
