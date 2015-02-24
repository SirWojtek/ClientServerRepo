
#include "ObjectsFacade.hpp"

#include <set>
#include <memory>

#include "objects/Object.hpp"
#include "objects/PlayerObject.hpp"

namespace model
{

ObjectsFacade::ObjectsFacade() :
    playerObject_(std::make_shared<PlayerObject>()) {}

void ObjectsFacade::addActiveObject(const Object& obj)
{
    activeObjects_.insert(std::make_shared<Object>(obj));
}

void ObjectsFacade::addInactiveObject(const Object& obj)
{
    inactiveObjects_.insert(std::make_shared<Object>(obj));
}

ObjectPtr ObjectsFacade::getPlayerObject()
{
    return playerObject_;
}

}
