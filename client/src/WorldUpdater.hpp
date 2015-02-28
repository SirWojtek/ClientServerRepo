#ifndef WORLD_UPDATER_HPP_
#define WORLD_UPDATER_HPP_

#include "IWorldUpdater.hpp"

#include "model/IObjectsFacade.hpp"
#include "ICommunicationService.hpp"
#include "model/objects/Object.hpp"

#include "common/messages/UpdateEnvironment.hpp"
#include "common/messages/UpdatePlayer.hpp"

class WorldUpdater : public IWorldUpdater
{
public:
    WorldUpdater(model::ObjectsFacadePtr objectsFacade, CommunicationServicePtr communicationServ);
    ~WorldUpdater();

    virtual void init();
    virtual void updateModel(bool isPlayerMoving);

private:
    model::ObjectPtr copyPlayerObject(const model::ObjectPtr playerObject) const;
    void sendUpdatePlayerMessage();
    common::UpdatePlayer getUpdatePlayerMessage(const model::ObjectPtr playerObject);
    common::UpdateEnvironment receiveUpdateEnvironmentMessage();
    void applyUpdatesToModel(common::UpdateEnvironment message);


    model::ObjectsFacadePtr objectsFacade_;
    model::ObjectPtr previousPlayerObject_;
    CommunicationServicePtr communicationServ_;
};

#endif  // WORLD_UPDATER_HPP_
