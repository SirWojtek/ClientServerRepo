#include <memory>
#include <thread>
#include <string>
#include <stdexcept>

#include "MessageReader.hpp"

ThreadPtr MessageReader::start()
{
    console_.info << "Starting reader thread";
    return std::make_shared<std::thread>(&MessageReader::readerLoop, this, shared_from_this());
}

void MessageReader::readerLoop(std::shared_ptr<MessageReader> self)
{
    console_.info << "Reader thread start OK";
    while (true)
    {
        std::shared_ptr<const std::string> message;
        try
        {
            message = tcpSocket_->read();
        }
        catch(const std::runtime_error& e)
        {
            console_.error << e.what();
            break;
        }

        if (message != nullptr)
        {
            console_.debug << "Message read: " << *message;
            messageQueue_->pushMessage(*message);
        }

        if (stop_.load())
        {
            break;
        }
    }
    console_.debug << "Reader thread ended";
}
