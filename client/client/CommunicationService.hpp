#pragma once

#include <memory>
#include <thread>
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
		MessageQueuePtr messageQueue, MessageWriterPtr messageWritter) :
			messageQueue_(messageQueue),
			tcpSocket_(std::move(tcpSocket)),
			messageWriter_(messageWritter),
			console_("CommunicationService") {}

	void startService(const std::string& host, const std::string& port);
	void putMessageInQueue(std::string&& message);
	void tearDown();

private:
	std::thread initService(std::string host, std::string port);

	MessageQueuePtr messageQueue_;
	TcpSocketPtr tcpSocket_;
	MessageWriterPtr messageWriter_;
	std::thread writerThread_;
	Console console_;
};
