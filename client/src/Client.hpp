#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <memory>

#include "IKeyboardController.hpp"
#include "IMovementManager.hpp"
#include "IWorldUpdater.hpp"

#include "view/IGameWindow.hpp"

#include "common/utilities/Console.hpp"

class Client
{
public:
    Client(KeyboardControllerPtr keyboardController,
        MovementManagerPtr movementManager, WorldUpdaterPtr worldUpdater,
        view::GameWindowPtr gameWindow);

    int start(int argc, char** argv);

private:
    void clientLoop();

    KeyboardControllerPtr keyboardController_;
    MovementManagerPtr movementManager_;
    WorldUpdaterPtr worldUpdater_;
    view::GameWindowPtr gameWindow_;
    Console console_;

    static const unsigned delayTime;
};
using ClientPtr = std::shared_ptr<Client>;

#endif
