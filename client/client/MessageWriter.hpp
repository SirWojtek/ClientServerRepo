#pragma once

#include <memory>
#include <string>
#include <future>

#include "IMessageActor.hpp"
#include "Console.hpp"
#include "ITcpSocket.hpp"
#include "IMessageQueue.hpp"


class MessageWriter : public IMessageActor
{
public:
	MessageWriter(TcpSocketPtr tcpSocket,
		MessageQueuePtr messageQueue) :
			tcpSocket_(tcpSocket),
			messageQueue_(messageQueue),
			console_("MessageWriter") {}

	void asyncSend(std::shared_ptr<std::string> message);
	bool asyncGet();

private:
	bool sendMessage(std::shared_ptr<std::string> message);

	std::shared_future<bool> writerThread_;
	MessageQueuePtr messageQueue_;
	TcpSocketPtr tcpSocket_;
	Console console_;
};
