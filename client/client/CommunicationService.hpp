#pragma once

#include <memory>
#include <future>
#include <string>

#include "ITcpSocket.hpp"
#include "IMessageQueue.hpp"
#include "IMessageActor.hpp"
#include "SharedVariable.hpp"
#include "Console.hpp"

class CommunicationService
{
public:
	CommunicationService(
		std::shared_ptr<ITcpSocket> tcpSocket,
		std::shared_ptr<IMessageActor> messageWriter) :
			tcpSocket_(tcpSocket),
			messageWriter_(messageWriter),
			console_("CommunicationService") {}

	void startService();
	void workTick();

private:
	void initService(std::string host, std::string port);
	std::shared_ptr<std::string> getMessage();

	std::shared_ptr<ITcpSocket> tcpSocket_;
	std::shared_ptr<SharedVariable<IMessageQueue>> messageQueue_;
	std::shared_ptr<IMessageActor> messageWriter_;
	Console console_;
};

