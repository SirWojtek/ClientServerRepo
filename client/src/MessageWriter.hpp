#ifndef MESSAGE_WRITTER_HPP_
#define MESSAGE_WRITTER_HPP_

#include <memory>
#include <string>
#include <thread>

#include "IMessageCommander.hpp"
#include "Console.hpp"
#include "ITcpSocket.hpp"
#include "IMessageQueue.hpp"


class MessageWriter : public IMessageCommander,
    public std::enable_shared_from_this<MessageWriter>
{
public:
    MessageWriter(TcpSocketPtr tcpSocket,
        MessageQueuePtr messageQueue) :
            tcpSocket_(tcpSocket),
            messageQueue_(messageQueue),
            console_("MessageWriter") {}

    virtual ThreadPtr start();

    static const std::string terminateCommand_;
private:
    void writerLoop(std::shared_ptr<MessageWriter> self);
    void writeMessage(std::string& netMessage);

    TcpSocketPtr tcpSocket_;
    MessageQueuePtr messageQueue_;
    Console console_;
};

#endif  // MESSAGE_WRITTER_HPP_
