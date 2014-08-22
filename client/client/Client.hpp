#pragma once

#include <memory>

#include "ITcpSocket.hpp"
#include "ThreadFactory.hpp"
#include "CommunicationService.hpp"
#include "Console.hpp"

class Client
{
public:
	Client(std::shared_ptr<ITcpSocket> tcpSocket);

	int start(int argc, char** argv);

private:
	void initConsole();

	std::shared_ptr<CommunicationService> communicationServ_;
	ThreadFactory threadFactory_;
    Console console_;
};
