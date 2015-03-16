
#include "MovementManager.hpp"

#include <string>
#include <stdexcept>
#include <algorithm>
#include <vector>

#include "IKeyboardController.hpp"
#include "model/IObjectsFacade.hpp"
#include "model/objects/Object.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <tmx/MapObject.h>

const std::string MovementManager::collisionLayerName = "Collision";

MovementManager::MovementManager(model::ObjectsFacadePtr objectFacade) :
    objectFacade_(objectFacade),
    console_("MovementManager") {}

using KeyDirection = IKeyboardController::KeyDirection;
using Position = model::Object::Position;

void MovementManager::singleTickMove(const KeyDirection& direction)
{
    if (direction == KeyDirection::None)
    {
        console_.debug << "Incorrect user input received";
        return;
    }

    changeUserPosition(direction);
}

void MovementManager::changeUserPosition(const KeyDirection& direction)
{
    model::ObjectPtr playerObj = objectFacade_->getPlayerObject();
    Position newPosition = getNewPosition(playerObj->position, direction);

    if (!isPlayerColliding(playerObj, newPosition))
    {
        playerObj->position = newPosition;
        return;
    }

    console_.debug << "Player is colliding with something";
}

Position MovementManager::getNewPosition(const Position& oldPos,
    const KeyDirection& dir) const
{
    Position newPos = oldPos;
    switch (dir)
    {
        case KeyDirection::Up:
            newPos.y -= delta;
            break;
        case KeyDirection::Down:
            newPos.y += delta;
            break;
        case KeyDirection::Right:
            newPos.x += delta;
            break;
        case KeyDirection::Left:
            newPos.x -= delta;
            break;
        default:
            throw std::runtime_error("Incorrect key direction");
    }

    newPos = correctPosition(newPos);

    console_.debug << "Old player position: " << oldPos.x << oldPos.y;
    console_.debug << "New player position: " << newPos.x << newPos.y;

    return newPos;
}

Position MovementManager::correctPosition(const Position& pos) const
{
    Position corrected;

    corrected.x = pos.x < 0 ? 0 : pos.x;
    corrected.y = pos.y < 0 ? 0 : pos.y;

    return corrected;
}

bool MovementManager::isPlayerColliding(const model::ObjectPtr& playerObj,
        model::Object::Position& newPosition) const
{
    using tmx::MapObject;
    std::vector<MapObject*> collidedObjects = objectFacade_->getCurrentMap()->getCollisionObjects(
        playerObj->getPositionRect());


    return std::find_if(collidedObjects.begin(), collidedObjects.end(),
        [&playerObj, &newPosition](const MapObject* object)
        {
            if (object->GetParent() == collisionLayerName)
            {
                return object->Contains(sf::Vector2f(
                    newPosition.x, newPosition.y)) ||
                object->Contains(sf::Vector2f(
                    newPosition.x, newPosition.y + playerObj->size)) ||
                object->Contains(sf::Vector2f(
                    newPosition.x + playerObj->size, newPosition.y)) ||
                object->Contains(sf::Vector2f(
                    newPosition.x + playerObj->size, newPosition.y + playerObj->size));

            }

            return false;
        }) != collidedObjects.end();
}
