#include <memory>

#include "Client.hpp"
#include "CommunicationService.hpp"
#include "common/socketServices/TcpSocket.hpp"
#include "common/socketServices/MessageQueue.hpp"
#include "common/socketServices/MessageWriter.hpp"
#include "common/socketServices/MessageReader.hpp"

CommunicationServicePtr createCommunicationService()
{
	MessageQueuePtr writerQueue =
		std::make_shared<MessageQueue>();
    MessageQueuePtr readerQueue =
        std::make_shared<MessageQueue>();
	TcpSocketPtr tcpSocket = std::make_shared<TcpSocket>();
	MessageCommanderPtr messageWritter = std::make_shared<MessageWriter>(tcpSocket, writerQueue);
	MessageCommanderPtr messageReader = std::make_shared<MessageReader>(tcpSocket, readerQueue);
    return std::make_shared<CommunicationService>(tcpSocket,
        writerQueue, messageWritter, readerQueue, messageReader);
}

int main(int argc, char** argv)
{
	CommunicationServicePtr communicationServ = createCommunicationService();
	Client client(communicationServ);
	return client.start(argc, argv);;
}
