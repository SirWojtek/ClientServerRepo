
#include "WorldUpdater.hpp"

#include <memory>

#include "model/IObjectsFacade.hpp"
#include "ICommunicationService.hpp"
#include "LoginService.hpp"
#include "model/objects/Object.hpp"

#include "common/messages/UpdateEnvironment.hpp"
#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageTypes.hpp"
#include "common/messages/MessageUtilities.hpp"

WorldUpdater::WorldUpdater(model::ObjectsFacadePtr objectsFacade,
    CommunicationServicePtr communicationServ) :
        objectsFacade_(objectsFacade),
        communicationServ_(communicationServ) {}

WorldUpdater::~WorldUpdater()
{
    communicationServ_->tearDown();
}

void WorldUpdater::init()
{
    communicationServ_->startService();

    model::ObjectPtr player = objectsFacade_->getPlayerObject();
    player->position = login(*communicationServ_);
    previousPlayerObject_ = copyPlayerObject(player);

    objectsFacade_->loadMaps();
}

void WorldUpdater::updateModel(bool isPlayerMoving)
{
    if (isPlayerMoving)
    {
        sendUpdatePlayerMessage();
    }

    std::shared_ptr<common::UpdateEnvironment> message = receiveUpdateEnvironmentMessage();

    if (message != nullptr)
    {
        applyUpdatesToModel(*message);
    }
}

model::ObjectPtr WorldUpdater::copyPlayerObject(const model::ObjectPtr playerObject) const
{
    return std::make_shared<model::Object>(*playerObject);
}

void WorldUpdater::sendUpdatePlayerMessage()
{
    model::ObjectPtr currentPlayerObject = objectsFacade_->getPlayerObject();
    common::UpdatePlayer message = getUpdatePlayerMessage(currentPlayerObject);

    communicationServ_->putMessageInQueue(message);

    previousPlayerObject_ = copyPlayerObject(objectsFacade_->getPlayerObject());
}

common::UpdatePlayer WorldUpdater::getUpdatePlayerMessage(const model::ObjectPtr playerObject)
{
    common::UpdatePlayer message;
    message.delta.first = playerObject->position.x - previousPlayerObject_->position.x;
    message.delta.second = playerObject->position.y - previousPlayerObject_->position.y;

    return message;
}

std::shared_ptr<common::UpdateEnvironment> WorldUpdater::receiveUpdateEnvironmentMessage()
{
    auto messageString = communicationServ_->getMessage(common::messagetype::UpdateEnvironment, false);

    if (messageString == nullptr)
    {
        return std::make_shared<common::UpdateEnvironment>();
    }

    auto updateMessagePtr = common::getMessage<common::UpdateEnvironment>(*messageString);

    if (updateMessagePtr == nullptr)
    {
        throw std::runtime_error("Error converting UpdateEnvironment message");
    }

    return updateMessagePtr;
}

void WorldUpdater::applyUpdatesToModel(const common::UpdateEnvironment& message)
{
    // TODO: write this method
}

