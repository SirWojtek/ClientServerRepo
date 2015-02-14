#ifndef MESSAGE_UTILITIES_HPP_
#define MESSAGE_UTILITIES_HPP_

#include <string>

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

messagetype::MessageType getMessageType(const std::string& jsonString);

template<class MessageT>
MessageT getMessage(const std::string& jsonString);

template<class MessageT>
std::string getMessageJson(const MessageT& msg);

}

#endif  // MESSAGE_UTILITIES_HPP_
