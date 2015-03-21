
#include "LoginService.hpp"

#include <stdexcept>

#include "common/messages/Login.hpp"
#include "common/messages/MessageUtilities.hpp"

std::string LoginService::filename = "login.info";

LoginService::LoginService(CommunicationServicePtr communicationServ) :
    communicationServ_(communicationServ),
    loginFile_(filename) {}

model::Object::Position LoginService::login()
{
    std::string username = getUserName();
    loginWithCredencial(username);

    return getPlayerPositionFromServer();
}

std::string LoginService::getUserName()
{
    std::string username;

    if (!loginFile_)
    {
        throw std::runtime_error("File with credencial (" + filename + ") cannot be open");
    }

    loginFile_ >> username;
    return username;
}

void LoginService::loginWithCredencial(const std::string& username)
{
    using namespace common;

    Login loginMessage = { username };
    OkResponse response = communicationServ_->putMessageInQueue(loginMessage);

    if (!response.serverAllows)
    {
        throw std::runtime_error("Login attempt failed");
    }
}

model::Object::Position LoginService::getPlayerPositionFromServer()
{
    // TODO: write this method
    return model::Object::Position();
}
