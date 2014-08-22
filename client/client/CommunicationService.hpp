#pragma once

#include <memory>
#include <future>
#include <string>

#include "ICommunicationService.hpp"
#include "ITcpSocket.hpp"
#include "IMessageQueue.hpp"
#include "MessageWriter.hpp"
#include "Console.hpp"

class CommunicationService : public ICommunicationService
{
public:
	CommunicationService(TcpSocketPtr tcpSocket,
		MessageQueuePtr messageQueue) :
			messageQueue_(messageQueue),
			tcpSocket_(tcpSocket),
			messageWriter_(std::make_shared<MessageWriter>(
				tcpSocket_, messageQueue_)),
			console_("CommunicationService") {}

	void startService();

private:
	void initService(std::string host, std::string port);

	MessageQueuePtr messageQueue_;
	TcpSocketPtr tcpSocket_;
	MessageActorPtr messageWriter_;
	Console console_;
};
