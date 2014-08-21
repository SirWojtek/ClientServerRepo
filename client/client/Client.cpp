#include <iostream>
#include <exception>

#include "Client.hpp"
#include "CommunicationService.hpp"
#include "ThreadFactory.hpp"

Client::Client(CommunicationService* communicationServ) :
	threadFactory_(new ThreadFactory()),
	communicationServ_(communicationServ),
	console_("Client") {}

int Client::start(int argc, char** argv)
{
	console_.info << "Starting client application";

	console_.info << "Starting network communication thread";
	std::thread t = threadFactory_->startThread(&CommunicationService::startService,
		*communicationServ_);

	t.join();
	console_.debug << "Thread joined";

	system("pause");
	return 0;
}

