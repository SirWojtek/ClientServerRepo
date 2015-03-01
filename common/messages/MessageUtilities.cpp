
#include "MessageUtilities.hpp"

#include "Messages.hpp"

#include <string>
#include <sstream>
#include <memory>
#include <map>

#include <cereal/archives/json.hpp>

namespace common
{
namespace
{

std::map<std::string, messagetype::MessageType> encodingMap =
{
    {UpdatePlayer::getName(), messagetype::UpdatePlayer},
    {UpdateEnvironment::getName(), messagetype::UpdateEnvironment},
    {OkResponse::getName(), messagetype::OkResponse}
};

}


messagetype::MessageType getMessageType(const std::string& jsonString)
{
    for (auto nameToType : encodingMap)
    {
        std::size_t pos = jsonString.find(nameToType.first);

        if (pos != std::string::npos)
        {
            return nameToType.second;
        }
    }

    return messagetype::Incorrect;
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
template std::shared_ptr<OkResponse> getMessage<OkResponse>(const std::string& jsonString);

template std::string getMessageJson<UpdateEnvironment>(const UpdateEnvironment& msg);
template std::string getMessageJson<UpdatePlayer>(const UpdatePlayer& msg);
template std::string getMessageJson<OkResponse>(const OkResponse& msg);

}
