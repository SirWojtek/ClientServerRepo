
#include "ObjectsFacade.hpp"

#include <set>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

#include "objects/Object.hpp"
#include "objects/PlayerObject.hpp"

#include "common/maps/MapContainer.hpp"

namespace model
{

namespace
{
    const Object::Position playerPosition = {0, 0};
    const unsigned playerSize = 10;
}

const std::vector<std::string> ObjectsFacade::mapFiles =
{
    "main.tmx"
};
const std::string ObjectsFacade::mapPath = "maps/";

ObjectsFacade::ObjectsFacade() :
    playerObject_(std::make_shared<Object>(playerPosition, playerSize)) {}

void ObjectsFacade::loadMaps()
{
    using namespace maps;

    for (const auto& mapFile : mapFiles)
    {
        maps_.emplace_back(MapContainer(mapPath));

        if (!maps_.back().object.loadMap(mapFile))
        {
            throw std::runtime_error("Map not loaded correctly");
        }
    }
}

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

ObjectsFacade::SafeMapContainer& ObjectsFacade::getCurrentMap()
{
    // TODO: current map deduction
    return maps_.back();
}

}
