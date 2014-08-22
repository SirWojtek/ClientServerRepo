#include <iostream>
#include <exception>

#include "Console.hpp"
#include "Client.hpp"
#include "CommunicationService.hpp"
#include "ThreadFactory.hpp"

int Client::start(int argc, char** argv)
{
	console_.info << "Starting network service";
	communicationServ_->startService();

	console_.debug << "Aplication going to exit";
	system("pause");
	return 0;
}
