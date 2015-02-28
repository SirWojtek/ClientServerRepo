#include "MessageUtilities.hpp"

#include <string>
#include <sstream>
#include <memory>

#include <cereal/archives/json.hpp>

#include "UpdateEnvironment.hpp"
#include "UpdatePlayer.hpp"

namespace common
{

messagetype::MessageType getMessageType(const std::string& jsonString)
{
    // TODO: implement this method
    return messagetype::UpdateEnvironment;
}

template<typename MessageT>
std::shared_ptr<MessageT> getMessage(const std::string& jsonString)
{
    std::shared_ptr<MessageT> result;

    try
    {
        std::stringstream stream(jsonString);
        cereal::JSONInputArchive archive(stream);

        archive(*result);
    }
    catch (...) {}

    return result;
}

template<typename MessageT>
std::string getMessageJson(const MessageT& msg)
{
    std::stringstream result;
    cereal::JSONOutputArchive archive(result);

    archive(msg);

    return result.str();
}

// function specialization
template std::shared_ptr<UpdateEnvironment> getMessage<UpdateEnvironment>(const std::string& jsonString);
template std::shared_ptr<UpdatePlayer> getMessage<UpdatePlayer>(const std::string& jsonString);
template std::string getMessageJson<UpdateEnvironment>(const UpdateEnvironment& msg);
template std::string getMessageJson<UpdatePlayer>(const UpdatePlayer& msg);

}
