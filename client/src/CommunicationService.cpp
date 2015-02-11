#include <thread>
#include <string>
#include <memory>

#include "IMessageQueue.hpp"
#include "IMessageCommander.hpp"
#include "CommunicationService.hpp"
#include "Console.hpp"
#include "ITcpSocket.hpp"

#include "messages/UpdateEnvironment.hpp"
#include "messages/UpdatePlayer.hpp"
#include "messages/MessageUtilities.hpp"

void CommunicationService::startService(
    const std::string& host, const std::string& port)
{
    tcpSocket_->connect(host, port);
    tcpSocket_ = nullptr;
    readerThread_ = messageReader_->start();
    writerThread_ = messageWriter_->start();
}

void CommunicationService::putMessageInQueue(const common::UpdateEnvironment& message)
{
    std::string json = common::getMessageJson<common::UpdateEnvironment>(message);
    writerQueue_->pushMessage(json);
    console_.info << "Message added to queue";
}

void CommunicationService::putMessageInQueue(const common::UpdatePlayer& message)
{
    std::string json = common::getMessageJson<common::UpdatePlayer>(message);
    writerQueue_->pushMessage(json);
    console_.info << "Message added to queue";
}

// TODO: receiveMessage(messageType)

void CommunicationService::tearDown()
{
    if (readerThread_->joinable())
    {
        messageReader_->stop();
        readerThread_->join();
    }

    if (writerThread_->joinable())
    {
        writerQueue_->waitForEmptyQueue();
        messageWriter_->stop();
        writerThread_->join();
    }

}
