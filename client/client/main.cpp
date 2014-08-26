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
	MessageActorPtr messageWritter = std::make_shared<MessageWriter>(tcpSocket, messageQueue);
	return std::make_shared<CommunicationService>(tcpSocket, messageQueue, messageWritter);
}

int main(int argc, char** argv)
{
	CommunicationServicePtr communicationServ = createCommunicationService();
	Client client(communicationServ);
	int returnCode = client.start(argc, argv);

	std::cout << std::endl << std::endl;
	system("pause");
	return returnCode;
}
