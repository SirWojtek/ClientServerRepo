#ifndef MOVEMENT_MANAGER_HPP_
#define MOVEMENT_MANAGER_HPP_

#include "IMovementManager.hpp"
#include "IKeyboardController.hpp"
#include "model/IObjectsFacade.hpp"

#include "common/utilities/Console.hpp"

class MovementManager : public IMovementManager
{
public:
    MovementManager(model::ObjectsFacadePtr objectFacade);

    virtual void singleTickMove(const IKeyboardController::KeyDirection& direction);

private:
    void changeUserPosition(const IKeyboardController::KeyDirection& direction);
    model::Object::Position getNewPosition(const model::Object::Position& oldPos,
        const IKeyboardController::KeyDirection& dir) const;

    model::ObjectsFacadePtr objectFacade_;
    Console console_;
    static const unsigned delta = 1;
};

#endif  // MOVEMENT_MANAGER_HPP_
