
#include "LoginService.hpp"

#include <stdexcept>
#include <string>
#include <fstream>

#include "common/messages/Login.hpp"
#include "common/messages/MessageUtilities.hpp"


namespace
{
const std::string filename = "login.info";

std::string getUserName()
{
    std::string username;
    std::ifstream loginFile(filename);

    if (!loginFile)
    {
        throw std::runtime_error("File with credencial (" + filename + ") cannot be open");
    }

    loginFile >> username;
    return username;
}

void loginWithCredencial(ICommunicationService& communicationServ,
    const std::string& username)
{
    using namespace common;

    Login loginMessage = { username };
    OkResponse response = communicationServ.putMessageInQueue(loginMessage);

    if (!response.serverAllows)
    {
        throw std::runtime_error("Login attempt failed");
    }
}

model::Object::Position getPlayerPositionFromServer()
{
    // TODO: write this method
    return model::Object::Position();
}

}

model::Object::Position login(ICommunicationService& communicationServ)
{
    std::string username = getUserName();
    loginWithCredencial(communicationServ, username);

    return getPlayerPositionFromServer();
}
