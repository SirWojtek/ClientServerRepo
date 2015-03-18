#ifndef MOVEMENT_MANAGER_HPP_
#define MOVEMENT_MANAGER_HPP_

#include "IMovementManager.hpp"

#include <string>

#include "IKeyboardController.hpp"
#include "FilePositionWriter.hpp"
#include "model/IObjectsFacade.hpp"

#include "common/utilities/Console.hpp"

class MovementManager : public IMovementManager
{
public:
    MovementManager(model::ObjectsFacadePtr objectFacade);

    virtual void singleTickMove(const IKeyboardController::KeyDirection& direction);

    static const int delta = 5;
private:
    void changeUserPosition(const IKeyboardController::KeyDirection& direction);
    model::Object::Position getNewPosition(const model::Object::Position& oldPos,
        const IKeyboardController::KeyDirection& dir) const;
    model::Object::Position correctPosition(const model::Object::Position& pos) const;
    bool isPlayerColliding(const model::ObjectPtr& playerObj,
        model::Object::Position& newPosition) const;

    model::ObjectsFacadePtr objectFacade_;
    FilePositionWriter positionWriter_;
    Console console_;

    static const std::string collisionLayerName;
};

#endif  // MOVEMENT_MANAGER_HPP_
