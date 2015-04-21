#ifndef LOGIN_SERVICE_HPP_
#define LOGIN_SERVICE_HPP_

#include "ICommunicationService.hpp"
#include "model/objects/Object.hpp"

model::Object::Position login(ICommunicationService& communicationServ);

#endif  // LOGIN_SERVICE_HPP_
