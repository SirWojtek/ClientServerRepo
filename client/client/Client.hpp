#pragma once

#include <memory>

#include "ThreadFactory.hpp"
#include "CommunicationService.hpp"
#include "Console.hpp"

class Client
{
public:
	Client(CommunicationServicePtr communicationServ) :
		communicationServ_(communicationServ),
		console_("Client") {}

	int start(int argc, char** argv);

private:
	void initConsole();

	CommunicationServicePtr communicationServ_;
	ThreadFactory threadFactory_;
    Console console_;
};
typedef std::shared_ptr<Client> ClientPtr;
