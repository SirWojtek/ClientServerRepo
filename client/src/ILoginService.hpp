#ifndef ILOGIN_SERVICE_HPP_
#define ILOGIN_SERVICE_HPP_

#include <memory>

#include "model/objects/Object.hpp"

class ILoginService
{
public:
    virtual model::Object::Position login() = 0;
};
using LoginServicePtr = std::shared_ptr<ILoginService>;

#endif  // ILOGIN_SERVICE_HPP_
