
#include "WorldUpdater.hpp"

#include <memory>

#include "model/IObjectsFacade.hpp"
#include "ICommunicationService.hpp"
#include "model/objects/Object.hpp"

#include "common/messages/UpdateEnvironment.hpp"
#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageTypes.hpp"
#include "common/messages/MessageUtilities.hpp"

WorldUpdater::WorldUpdater(model::ObjectsFacadePtr objectsFacade,
    CommunicationServicePtr communicationServ) :
        objectsFacade_(objectsFacade),
        communicationServ_(communicationServ)
    {
        communicationServ_->startService();
        previousPlayerObject_ = copyPlayerObject(objectsFacade_->getPlayerObject());
    }

WorldUpdater::~WorldUpdater()
{
    communicationServ_->tearDown();
}

void WorldUpdater::updateModel(bool isPlayerMoving)
{
    if (isPlayerMoving)
    {
        sendUpdatePlayerMessage();
    }

    common::UpdateEnvironment message = receiveUpdateEnvironmentMessage();
    applyUpdatesToModel(message);
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

common::UpdateEnvironment WorldUpdater::receiveUpdateEnvironmentMessage()
{
    auto messageString = communicationServ_->getMessage(common::messagetype::UpdateEnvironment);
    return common::getMessage<common::UpdateEnvironment>(*messageString);
}

void WorldUpdater::applyUpdatesToModel(common::UpdateEnvironment message)
{
    // TODO: write this method
}

