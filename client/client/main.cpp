#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <cereal/archives/json.hpp>

#include "Client.hpp"
#include "CommunicationService.hpp"
#include "TcpSocket.hpp"
#include "MessageQueue.hpp"
#include "MessageWriter.hpp"

CommunicationServicePtr createCommunicationService()
{
	MessageQueuePtr messageQueue =
		std::make_shared<MessageQueue>();
	TcpSocketPtr tcpSocket = std::make_shared<TcpSocket>();
	return std::make_shared<CommunicationService>(tcpSocket, messageQueue);
}

int main(int argc, char** argv)
{
	CommunicationServicePtr communicationServ = createCommunicationService();
	Client client(communicationServ);
	return client.start(argc, argv);
}
