#pragma once

#include <memory>
#include <string>

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
	void receiveAnswer(std::shared_ptr<const std::string> answer);

	CommunicationServicePtr communicationServ_;
    Console console_;

	static std::string host, port;
};
typedef std::shared_ptr<Client> ClientPtr;
