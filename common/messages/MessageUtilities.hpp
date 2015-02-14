#ifndef MESSAGE_UTILITIES_HPP_
#define MESSAGE_UTILITIES_HPP_

#include <string>

namespace common
{

struct UpdateEnvironment;
struct UpdatePlayer;

namespace messagetype
{
enum MessageType
{
    UpdateEnvironment,
    UpdatePlayer
};
}

messagetype::MessageType getMessageType(const std::string& jsonString);

template<typename MessageT>
MessageT getMessage(const std::string& jsonString);

template<typename MessageT>
std::string getMessageJson(const MessageT& msg);

}

#endif  // MESSAGE_UTILITIES_HPP_
