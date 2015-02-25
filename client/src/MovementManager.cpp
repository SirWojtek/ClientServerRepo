
#include "MovementManager.hpp"

#include <stdexcept>

#include "IKeyboardController.hpp"
#include "model/IObjectsFacade.hpp"
#include "model/objects/Object.hpp"

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
    playerObj->position = newPosition;
}

Position MovementManager::getNewPosition(const Position& oldPos,
    const KeyDirection& dir) const
{
    Position newPos = oldPos;
    switch (dir)
    {
        case KeyDirection::Up:
            newPos.y += delta;
            break;
        case KeyDirection::Down:
            newPos.y -= delta;
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

    console_.debug << "Old player position: " << oldPos.x << oldPos.y;
    console_.debug << "New player position: " << newPos.x << newPos.y;

    return newPos;
}
