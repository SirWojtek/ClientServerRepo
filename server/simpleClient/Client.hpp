#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <memory>
#include <string>
#include <ctime>
#include <chrono>
#include <ratio>

#include "ICommunicationService.hpp"
#include "IKeyboardController.hpp"
#include "common/utilities/Console.hpp"
#include "common/messages/MessageUtilities.hpp"

using namespace std::chrono;

class Client
{
public:
    Client(CommunicationServicePtr communicationServ, KeyboardControllerPtr keyboardController);

    int start(int argc, char** argv);

private:
    void init();
    void tearDown();
    void clientLoop(int clientNumber);
    void login(int clientNumber);

    CommunicationServicePtr communicationServ_;
    KeyboardControllerPtr keyboardController_;
    Console console_;
    unsigned amountOfMessagesSent_; 
    duration<double> totalTimeBetweenMessageReceiveAndSend_;
    high_resolution_clock::time_point timeBetweenMessageReceiveAndSend_;

    static std::string host, port;
};
using ClientPtr = std::shared_ptr<Client>;

#endif