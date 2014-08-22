#include <iostream>
#include <exception>

#include "Console.hpp"
#include "Client.hpp"
#include "CommunicationService.hpp"
#include "ThreadFactory.hpp"
#include "MessageQueue.hpp"
#include "MessageWriter.hpp"

Client::Client(std::shared_ptr<ITcpSocket> tcpSocket) :
		communicationServ_(std::make_shared<CommunicationService>(
		tcpSocket, std::make_shared<MessageWriter>(
			std::make_shared<SharedVariable<MessageQueue>>()))),
		console_("Client") {}

int Client::start(int argc, char** argv)
{
	console_.info << "Starting client application";

	console_.info << "Starting network communication thread";
	std::thread t = threadFactory_.startThread(&CommunicationService::startService,
		*communicationServ_);

	t.join();
	console_.debug << "Thread joined";


	system("pause");
	return 0;
}
