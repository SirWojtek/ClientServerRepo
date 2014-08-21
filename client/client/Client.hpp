#pragma once

#include <memory>

#include "ThreadFactory.hpp"
#include "CommunicationService.hpp"
#include "Console.hpp"

class Client
{
public:
	Client(CommunicationService* communicationServ);

	int start(int argc, char** argv);

private:
	std::unique_ptr<ThreadFactory> threadFactory_;
	std::shared_ptr<CommunicationService> communicationServ_;
    Console console_;
};

