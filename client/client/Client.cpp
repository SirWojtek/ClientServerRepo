#include <iostream>
#include <exception>
#include <string>

#include "Console.hpp"
#include "Client.hpp"
#include "CommunicationService.hpp"
#include "ThreadFactory.hpp"

std::string Client::host = "127.0.0.1";
std::string Client::port = "1234";

int Client::start(int argc, char** argv)
{
	console_.info << "Starting network service";
	communicationServ_->startService(host, port);

	console_.debug << "Aplication going to exit";
	communicationServ_->tearDown();

	return 0;
}
