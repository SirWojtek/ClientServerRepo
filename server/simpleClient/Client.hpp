#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <memory>
#include <string>

#include "ICommunicationService.hpp"
#include "IKeyboardController.hpp"
#include "common/utilities/Console.hpp"
#include "common/messages/MessageUtilities.hpp"

class Client
{
public:
    Client(CommunicationServicePtr communicationServ, KeyboardControllerPtr keyboardController);

    int start(int argc, char** argv);

private:
    void init();
    void tearDown();
    void clientLoop();
    void login();

    CommunicationServicePtr communicationServ_;
    KeyboardControllerPtr keyboardController_;
    Console console_;

    static std::string host, port;
};
using ClientPtr = std::shared_ptr<Client>;

#endif