#include <iostream>
#include <exception>
#include <string>

#include "Client.hpp"
#include "ICommunicationService.hpp"
#include "IKeyboardController.hpp"

#include "common/utilities/Console.hpp"
#include "common/messages/UpdatePlayer.hpp"
#include "common/socketServices/ITcpSocket.hpp"

std::string Client::host = "127.0.0.1";
std::string Client::port = "4001";


Client::Client(CommunicationServicePtr communicationServ,
    KeyboardControllerPtr keyboardController) :
        communicationServ_(communicationServ),
        keyboardController_(keyboardController),
        console_("Client") {}

int Client::start(int argc, char** argv)
{
    try
    {
        init();
        clientLoop();
        tearDown();
    }
    catch (std::runtime_error& e)
    {
        console_.error << e.what();
    }

    return 0;
}

void Client::init()
{
    ILoger::filePrint_ = true;
    console_.info << "Starting network service";
    communicationServ_->startService(host, port);
}

void Client::tearDown()
{
    console_.debug << "Aplication going to exit";
    communicationServ_->tearDown();
}

void Client::clientLoop()
{
    // common::UpdatePlayer msg;
    // communicationServ_->putMessageInQueue(msg);

    while (!keyboardController_->wasExitKeyPressed())
    {
        IKeyboardController::KeyDirection direction = keyboardController_->getKeyboardInput();

        if (direction == IKeyboardController::None)
        {
            continue;
        }

        console_.debug << "Correct keyboard input received";

    }
}

