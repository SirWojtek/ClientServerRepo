#ifndef MESSAGE_UTILITIES_HPP_
#define MESSAGE_UTILITIES_HPP_

#include <string>
#include <sstream>

#include <cereal/archives/json.hpp>

#include "UpdateEnvironment.hpp"
#include "UpdatePlayer.hpp"

namespace common
{

namespace messagetype
{
enum MessageType
{
    UpdateEnvironment,
    UpdatePlayer
};
}

messagetype::MessageType getMessageType(const std::string& jsonString)
{
    return messagetype::UpdateEnvironment;
}

template<class MessageT>
MessageT getMessage(const std::string& jsonString)
{
    MessageT result;
    std::stringstream stream(jsonString);
    cereal::JSONInputArchive archive(stream);

    archive(result);

    return result;
}

template<class MessageT>
std::string getMessageJson(const MessageT& msg)
{
    std::stringstream result;
    cereal::JSONOutputArchive archive(result);

    archive(msg);

    return result.str();
}

}

#endif  // MESSAGE_UTILITIES_HPP_
