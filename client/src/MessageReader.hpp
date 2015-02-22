#ifndef MESSAGE_READER_HPP_
#define MESSAGE_READER_HPP_

#include <memory>
#include <string>
#include <thread>

#include "IMessageCommander.hpp"
#include "common/utilities/Console.hpp"
#include "common/utilities/ITcpSocket.hpp"
#include "IMessageQueue.hpp"


class MessageReader : public IMessageCommander,
    public std::enable_shared_from_this<MessageReader>
{
public:
    MessageReader(TcpSocketPtr tcpSocket,
        MessageQueuePtr messageQueue) :
            tcpSocket_(tcpSocket),
            messageQueue_(messageQueue),
            console_("MessageReader") {}

    virtual ThreadPtr start();

private:
    void readerLoop(std::shared_ptr<MessageReader> self);

    TcpSocketPtr tcpSocket_;
    MessageQueuePtr messageQueue_;
    Console console_;
};

#endif  // MESSAGE_READER_HPP_
