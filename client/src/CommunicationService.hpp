#ifndef COMMUNICATION_SERVICE_HPP_
#define COMMUNICATION_SERVICE_HPP_

#include <memory>
#include <thread>
#include <string>
#include <map>

#include "ICommunicationService.hpp"
#include "ITcpSocket.hpp"
#include "IMessageQueue.hpp"
#include "IMessageCommander.hpp"
#include "Console.hpp"

#include "messages/MessageUtilities.hpp"
#include "messages/UpdatePlayer.hpp"

class CommunicationService : public ICommunicationService
{
public:
    CommunicationService(TcpSocketPtr tcpSocket,
        MessageQueuePtr writerQueue, MessageCommanderPtr messageWritter,
        MessageQueuePtr readerQueue, MessageCommanderPtr messageReader) :
            tcpSocket_(std::move(tcpSocket)),
            writerQueue_(writerQueue),
            messageWriter_(messageWritter),
            readerQueue_(readerQueue),
            messageReader_(messageReader),
            console_("CommunicationService") {}

    void startService(const std::string& host, const std::string& port);
    void putMessageInQueue(const common::UpdatePlayer& message);
    std::shared_ptr<std::string> getMessage(const common::messagetype::MessageType& type);
    void tearDown();

private:
    bool isMessageOfTypeAlreadyReceived(const common::messagetype::MessageType& type);
    std::shared_ptr<std::string> getMessageOfTypeAlreadyReceived(
        const common::messagetype::MessageType& type);
    std::shared_ptr<std::string> getMessageOfTypeNotReceived(
        const common::messagetype::MessageType& type);

    TcpSocketPtr tcpSocket_;

    MessageQueuePtr writerQueue_;
    MessageCommanderPtr messageWriter_;
    ThreadPtr writerThread_;

    MessageQueuePtr readerQueue_;
    MessageCommanderPtr messageReader_;
    ThreadPtr readerThread_;

    std::multimap<common::messagetype::MessageType, std::shared_ptr<std::string>> receivedMessages_;

    Console console_;
};

#endif  // COMMUNICATION_SERVICE_HPP_
