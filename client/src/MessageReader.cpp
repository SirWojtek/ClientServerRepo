#include <memory>
#include <thread>
#include <string>
#include <stdexcept>

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
        std::string message;
        try
        {
            message = *tcpSocket_->read();
        }
        catch(const std::runtime_error& e)
        {
            console_.error << e.what();
            break;
        }

        messageQueue_->pushMessage(message);

        if (stop_.load())
        {
            break;
        }
    }
    console_.debug << "Reader thread ended";
}
