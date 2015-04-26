
#include <memory>

#include "Client.hpp"
#include "CommunicationService.hpp"
#include "KeyboardController.hpp"
#include "KeyGetter.hpp"

#include "common/socketServices/TcpSocket.hpp"
#include "common/socketServices/MessageQueue.hpp"
#include "common/socketServices/MessageWriter.hpp"
#include "common/socketServices/MessageReader.hpp"

std::shared_ptr<CommunicationService> createCommunicationService()
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

KeyboardControllerPtr createKeyboardController()
{
    return std::make_shared<KeyboardController>(std::make_shared<KeyGetter>());
}

int main(int argc, char** argv)
{
	assert(argc>1 && "Run this program with a client number please!");
	ILoger::setDebugPrint(true);
	
	std::shared_ptr<CommunicationService> communicationServ = createCommunicationService();
    KeyboardControllerPtr keyboardController = createKeyboardController();

	Client client(communicationServ, keyboardController);
	return client.start(argc, argv);;
}
