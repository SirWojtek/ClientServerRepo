#include <iostream>
#include <exception>
#include <string>

#include "Console.hpp"
#include "Client.hpp"
#include "CommunicationService.hpp"

std::string Client::host = "127.0.0.1";
std::string Client::port = "1234";

using namespace std::placeholders;

int Client::start(int argc, char** argv)
{
    try
    {
        console_.info << "Starting network service";
        communicationServ_->startService(host, port);

        communicationServ_->putMessageInQueue(
            { "test:test1" });

        console_.debug << "Aplication going to exit";
        communicationServ_->tearDown();
    }
    catch (std::runtime_error& e)
    {
        console_.error << e.what();
    }

    return 0;
}

