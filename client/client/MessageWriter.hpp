#pragma once

#include <memory>
#include <string>
#include <thread>

#include "IMessageWriter.hpp"
#include "Console.hpp"
#include "ITcpSocket.hpp"
#include "IMessageQueue.hpp"


class MessageWriter : public IMessageWriter,
	public std::enable_shared_from_this<MessageWriter>
{
public:
	MessageWriter(TcpSocketPtr tcpSocket,
		MessageQueuePtr messageQueue) :
			tcpSocket_(tcpSocket),
			messageQueue_(messageQueue),
			console_("MessageWriter") {}

	std::thread start();

	static const std::string terminateCommand_;
private:
	void writerLoop(std::shared_ptr<MessageWriter> self);

	MessageQueuePtr messageQueue_;
	TcpSocketPtr tcpSocket_;
	Console console_;
};
