#ifndef MESSAGE_UTILITIES_HPP_
#define MESSAGE_UTILITIES_HPP_

#include <string>
#include <memory>

#include "MessageTypes.hpp"

namespace common
{

struct UpdateEnvironment;
struct UpdatePlayer;

messagetype::MessageType getMessageType(const std::string& jsonString);

template<typename MessageT>
std::shared_ptr<MessageT> getMessage(const std::string& jsonString);

template<typename MessageT>
std::string getMessageJson(const MessageT& msg);

}

#endif  // MESSAGE_UTILITIES_HPP_
