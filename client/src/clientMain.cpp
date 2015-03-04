
#include <memory>

#include "Client.hpp"
#include "CommunicationService.hpp"
#include "KeyboardController.hpp"
#include "KeyGetter.hpp"
#include "MovementManager.hpp"
#include "WorldUpdater.hpp"

#include "model/ObjectsFacade.hpp"
#include "view/GameWindow.hpp"

#include "common/socketServices/TcpSocket.hpp"
#include "common/socketServices/MessageQueue.hpp"
#include "common/socketServices/MessageWriter.hpp"
#include "common/socketServices/MessageReader.hpp"
#include "common/utilities/Console.hpp"

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

KeyboardControllerPtr createKeyboardController()
{
    return std::make_shared<KeyboardController>(std::make_shared<KeyGetter>());
}

model::ObjectsFacadePtr createObjectsFacade()
{
    return std::make_shared<model::ObjectsFacade>();
}

MovementManagerPtr createMovementManager(model::ObjectsFacadePtr facade)
{
    return std::make_shared<MovementManager>(facade);
}

WorldUpdaterPtr createWorldUpdater(model::ObjectsFacadePtr facade)
{
    CommunicationServicePtr communicationServ = createCommunicationService();
    return std::make_shared<WorldUpdater>(facade, communicationServ);
}

view::GameWindowPtr createGameWindow()
{
    return std::make_shared<view::GameWindow>();
}

int main(int argc, char** argv)
{
    ILoger::setFilePrint(true);
    model::ObjectsFacadePtr objectsFacade = createObjectsFacade();
    view::GameWindowPtr gameWindow = createGameWindow();

    KeyboardControllerPtr keyboardController = createKeyboardController();
    MovementManagerPtr movementManager = createMovementManager(objectsFacade);
    WorldUpdaterPtr worldUpdater = createWorldUpdater(objectsFacade);

	Client client(keyboardController, movementManager, worldUpdater, gameWindow);
	return client.start(argc, argv);
}
