#include <stdlib.h>
#include <time.h>
#include <chrono>

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

using namespace common;

Client::Client(CommunicationServicePtr communicationServ,
    KeyboardControllerPtr keyboardController) :
        communicationServ_(communicationServ),
        keyboardController_(keyboardController),
        console_("Client")
{
    srand (time(NULL));
}

int Client::start(int argc, char** argv)
{
    try
    {
        init();
        login();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
    ILoger::filePrint_ = false;
    console_.info << "Starting network service";
    communicationServ_->startService();
}

void Client::tearDown()
{
    console_.debug << "Aplication going to exit";
    communicationServ_->tearDown();
}

void Client::clientLoop()
{

    for (int i=0; i<200; i++)
    {
        IKeyboardController::KeyDirection direction = keyboardController_->getKeyboardInput();

        if (direction == IKeyboardController::None)
        {
            continue;
        }

        common::UpdatePlayer message;
        switch(rand() % 4)
        {
            case 0:
                message.delta.first = 0;
                message.delta.second = 5;
                break;
            case 1:
                message.delta.first = 0;
                message.delta.second = -5;
                break;
            case 2:
                message.delta.first = 5;
                message.delta.second = 0;
                break;
            case 3:
                message.delta.first = -5;
                message.delta.second = 0;
                break;
            default:
                message.delta.first = 0;
                message.delta.second = 0;
                break;
        }
        OkResponse response = communicationServ_->putMessageInQueue(message);

        if (!response.serverAllows)
        {
            throw std::runtime_error("Login attempt failed");
        }

        //console_.debug << "Correct keyboard input received";
    }
}

void Client::login()
{
    Login loginMessage;
    loginMessage.playerName = "Gettor";
    OkResponse response = communicationServ_->putMessageInQueue(loginMessage);

    if (!response.serverAllows)
    {
        throw std::runtime_error("Login attempt failed");
    }
}