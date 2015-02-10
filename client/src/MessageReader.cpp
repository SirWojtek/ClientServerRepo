#include <memory>
#include <thread>
#include <string>

#include "NetworkMessage.hpp"
#include "MessageReader.hpp"

ThreadPtr MessageReader::start()
{
    console_.info << "Starting reader thread";
    return std::make_shared<std::thread>(&MessageReader::readerLoop, this, shared_from_this());
}

void MessageReader::readerLoop(std::shared_ptr<MessageReader> self)
{
    console_.info << "Writer thread start OK";
    while (true)
    {
        std::string message = *tcpSocket_->read();
        messageQueue_->pushMessage(message);

        if (stop_.load())
        {
            break;
        }
    }
    console_.debug << "Reader thread ended";
}
