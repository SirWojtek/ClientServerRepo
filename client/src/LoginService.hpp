#ifndef LOGIN_SERVICE_HPP_
#define LOGIN_SERVICE_HPP_

#include "ILoginService.hpp"

#include <fstream>
#include <string>

#include "ICommunicationService.hpp"

class LoginService : public ILoginService
{
public:
    LoginService(CommunicationServicePtr communicationServ);

    virtual model::Object::Position login();
private:
    std::string getUserName();
    void loginWithCredencial(const std::string& username);
    model::Object::Position getPlayerPositionFromServer();

    CommunicationServicePtr communicationServ_;
    std::ifstream loginFile_;
    static std::string filename;
};

#endif  // LOGIN_SERVICE_HPP_
