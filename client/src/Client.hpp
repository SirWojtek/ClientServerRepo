#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <memory>

#include "ICommunicationService.hpp"
#include "IKeyboardController.hpp"
#include "IMovementManager.hpp"
#include "IWorldUpdater.hpp"

#include "common/utilities/Console.hpp"

class Client
{
public:
    Client(KeyboardControllerPtr keyboardController,
        MovementManagerPtr movementManager, WorldUpdaterPtr worldUpdater);

    int start(int argc, char** argv);

private:
    void clientLoop();

    CommunicationServicePtr communicationServ_;
    KeyboardControllerPtr keyboardController_;
    MovementManagerPtr movementManager_;
    WorldUpdaterPtr worldUpdater_;
    Console console_;
};
using ClientPtr = std::shared_ptr<Client>;

#endif
