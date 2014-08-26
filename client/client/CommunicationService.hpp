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
		MessageQueuePtr messageQueue, MessageActorPtr messageWritter) :
			messageQueue_(messageQueue),
			tcpSocket_(tcpSocket),
			messageWriter_(messageWritter),
			console_("CommunicationService") {}

	void startService(const std::string& host, const std::string& port);

private:
	void initService(std::string host, std::string port);

	MessageQueuePtr messageQueue_;
	TcpSocketPtr tcpSocket_;
	MessageActorPtr messageWriter_;
	Console console_;
};
