#ifndef MESSAGE_UTILITIES_HPP_
#define MESSAGE_UTILITIES_HPP_

#include <string>

#include "UpdateEnvironment.hpp"
#include "UpdatePlayer.hpp"

namespace common
{

enum MessageType
{
    UpdateEnvironment,
    UpdatePlayer
};

MessageType getMessageType(const std:string& jsonString)
{
    // TODO: write method reckognizing type of message
}

UpdateEnvironment getEnvironmentMessage(const std::string& jsonString)
{
    // TODO: wrote method converting JSON to UpdateEnvironment message
}

}

#endif  // MESSAGE_UTILITIES_HPP_
