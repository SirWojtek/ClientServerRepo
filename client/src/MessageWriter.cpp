#include <memory>
#include <thread>
#include <string>

#include "MessageWriter.hpp"

const std::string MessageWriter::terminateCommand_ = "TERMINATE";

ThreadPtr MessageWriter::start()
{
    console_.info << "Starting writer thread";
    return std::make_shared<std::thread>(&MessageWriter::writerLoop, this, shared_from_this());
}

void MessageWriter::writerLoop(std::shared_ptr<MessageWriter> self)
{
    console_.info << "Writer thread start OK";
    while (true)
    {
        std::string netMessage = messageQueue_->popMessage();
        writeMessage(netMessage);

        if (stop_.load())
        {
            break;
        }
    }
    console_.debug << "Writer thread ended";
}

void MessageWriter::writeMessage(std::string& netMessage)
{
    console_.info << "Message to send: " << netMessage;
    tcpSocket_->write(netMessage);
    console_.info << "Message sended";
}
