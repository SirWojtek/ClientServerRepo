
#include <memory>

#include "Client.hpp"
#include "CommunicationService.hpp"
#include "KeyboardController.hpp"
#include "MovementManager.hpp"
#include "WorldUpdater.hpp"

#include "model/ObjectsFacade.hpp"
#include "view/GameWindow.hpp"
#include "view/ModelPainter.hpp"

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
    return std::make_shared<KeyboardController>();
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

view::GameWindowPtr createGameWindow(model::ObjectsFacadePtr objectsFacade)
{
    return std::make_shared<view::GameWindow>(std::make_shared<view::ModelPainter>(objectsFacade));
}

int main(int argc, char** argv)
{
    model::ObjectsFacadePtr objectsFacade = createObjectsFacade();
    view::GameWindowPtr gameWindow = createGameWindow(objectsFacade);

    KeyboardControllerPtr keyboardController = createKeyboardController();
    MovementManagerPtr movementManager = createMovementManager(objectsFacade);
    WorldUpdaterPtr worldUpdater = createWorldUpdater(objectsFacade);

	Client client(keyboardController, movementManager, worldUpdater, gameWindow);
	return client.start(argc, argv);
}
