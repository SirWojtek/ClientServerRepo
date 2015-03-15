#ifndef MESSAGE_TYPES_HPP_
#define MESSAGE_TYPES_HPP_

namespace common
{
namespace messagetype
{
enum MessageType
{
    Incorrect,
    UpdateEnvironment,
    UpdatePlayer,
    OkResponse,
    Login,
    CurrentPlayerPosition,
    Logout
};
}
}

#endif  // MESSAGE_TYPES_HPP_