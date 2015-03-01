
#include "MessageUtilities.hpp"

#include "Messages.hpp"

#include <string>
#include <sstream>
#include <memory>
#include <map>
#include <stdexcept>

#include <cereal/archives/json.hpp>
#include <cereal/details/helpers.hpp>

namespace common
{
namespace
{

std::map<std::string, messagetype::MessageType> encodingMap =
{
    {UpdatePlayer::type(), messagetype::UpdatePlayer},
    {UpdateEnvironment::type(), messagetype::UpdateEnvironment},
    {OkResponse::type(), messagetype::OkResponse},
    {NoChanges::type(), messagetype::NoChanges}
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
    std::shared_ptr<MessageT> result = std::make_shared<MessageT>();

    std::stringstream stream(jsonString);

    try
    {
        cereal::JSONInputArchive archive(stream);
        archive(*result);
    }
    catch (cereal::Exception e)
    {
        result = nullptr;
    }


    return result;
}

template<typename MessageT>
std::string getMessageJson(const MessageT& msg)
{
    std::stringstream result;

    {
        cereal::JSONOutputArchive archive(result);

        archive(msg);
    }

    return result.str();
}

// function specialization
template std::shared_ptr<UpdateEnvironment> getMessage<UpdateEnvironment>(const std::string& jsonString);
template std::shared_ptr<UpdatePlayer> getMessage<UpdatePlayer>(const std::string& jsonString);
template std::shared_ptr<OkResponse> getMessage<OkResponse>(const std::string& jsonString);
template std::shared_ptr<NoChanges> getMessage<NoChanges>(const std::string& jsonString);

template std::string getMessageJson<UpdateEnvironment>(const UpdateEnvironment& msg);
template std::string getMessageJson<UpdatePlayer>(const UpdatePlayer& msg);
template std::string getMessageJson<OkResponse>(const OkResponse& msg);
template std::string getMessageJson<NoChanges>(const NoChanges& msg);

}
