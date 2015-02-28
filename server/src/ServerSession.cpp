#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <thread>
#include <string>
#include <memory>
#include <utility>
#include <map>
#include <stdexcept>

#include "ServerSession.hpp"
#include "common/messages/MessageUtilities.hpp"

using common::messagetype::MessageType;
using boost::asio::ip::tcp;

tcp::socket& ServerSession::getSocket()
{
	return *(socket_->getSocket());
}

void ServerSession::start()
{
    // std::shared_ptr<const std::string> messageReceived = socket_->read();
    // std::string messageToBeSent(*messageReceived);
    // socket_->write(messageToBeSent);
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
        if (messageIndex != noMessage_)
        {
            sendResponse();
        }
    }
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
    common::OkResponse okMessage_;
    okMessage_.serverAllows = true;
    std::string json = common::getMessageJson<common::OkResponse>(okMessage_);
    writerQueue_->pushMessage(json);
    console_.debug << "OkMessage added to queue";
}