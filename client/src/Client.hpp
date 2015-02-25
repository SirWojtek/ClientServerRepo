#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <memory>
#include <string>

#include "ICommunicationService.hpp"
#include "IKeyboardController.hpp"
#include "IMovementManager.hpp"

#include "common/utilities/Console.hpp"

class Client
{
public:
    Client(CommunicationServicePtr communicationServ, KeyboardControllerPtr keyboardController,
        MovementManagerPtr movementManager);

    int start(int argc, char** argv);

private:
    void init();
    void tearDown();
    void clientLoop();

    CommunicationServicePtr communicationServ_;
    KeyboardControllerPtr keyboardController_;
    MovementManagerPtr movementManager_;
    Console console_;

    static std::string host, port;
};
using ClientPtr = std::shared_ptr<Client>;

#endif