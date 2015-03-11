#include <thread>
#include <stdexcept>

#include "server/src/ServerSession.hpp"
#include "common/messages/MessageUtilities.hpp"

using common::messagetype::MessageType;
using boost::asio::ip::tcp;

tcp::socket& ServerSession::getSocket()
{
	return *(socket_->getSocket());
}

std::shared_ptr<std::thread> ServerSession::start()
{
    return std::make_shared<std::thread>(&ServerSession::startThreadsAndRun,
        this, shared_from_this());
}

void ServerSession::startThreadsAndRun(std::shared_ptr<ServerSession> self)
{
    readerThread_ = reader_->start();
    writerThread_ = writer_->start();

    console_.info << "Service started";
    runSession();
}

void ServerSession::runSession()
{
    int messageIndex;
    while(true)
    {
        messageIndex = getMessage();
        writerQueue_->waitForEmptyQueue();
        if (messageIndex != noMessage_)
        {
            sendResponse();
        }
        if (stop_.load())
        {
            break;
        }
    }
    console_.info << "Server session stopped.";
}

void ServerSession::stop()
{
    stop_.exchange(true);
}

int ServerSession::getMessage()
{
    std::shared_ptr<std::string> messageString;
    if (messageString = readerQueue_->popMessage())
    {
        MessageType receivedMessageType = common::getMessageType(*messageString);
        receivedMessages_.insert(
                std::pair<MessageType, std::shared_ptr<std::string>>(
                    receivedMessageType, messageString));
        return (receivedMessages_.size()-1); // index of just inserted value
    }
    return noMessage_;
}

void ServerSession::sendResponse()
{
    common::OkResponse okMessage;
    okMessage.serverAllows = true;
    std::string json = common::getMessageJson<common::OkResponse>(okMessage);
    writerQueue_->pushMessage(json);
    console_.debug << "OkMessage added to queue";
}
