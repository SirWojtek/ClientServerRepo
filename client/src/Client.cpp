
#include <iostream>
#include <exception>
#include <chrono>
#include <thread>

#include "Client.hpp"
#include "ICommunicationService.hpp"


const unsigned Client::delayTime = 50;

Client::Client(KeyboardControllerPtr keyboardController,
    MovementManagerPtr movementManager,
    WorldUpdaterPtr worldUpdater,
    view::GameWindowPtr gameWindow) :
        keyboardController_(keyboardController),
        movementManager_(movementManager),
        worldUpdater_(worldUpdater),
        gameWindow_(gameWindow),
        console_("Client") {}

int Client::start(int argc, char** argv)
{
    try
    {
        worldUpdater_->init();
        gameWindow_->startWindowThread();
        clientLoop();

        gameWindow_->tearDown();
    }
    catch (std::runtime_error& e)
    {
        console_.error << e.what();

        gameWindow_->tearDown();
        return -1;
    }

    return 0;
}

void Client::clientLoop()
{
    while (!keyboardController_->wasExitKeyPressed())
    {
        IKeyboardController::KeyDirection direction = keyboardController_->getKeyboardInput();

        movementManager_->singleTickMove(direction);

        // TODO: change to responce from MovementManager
        worldUpdater_->updateModel(direction != IKeyboardController::None);

        std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));
    }
}

