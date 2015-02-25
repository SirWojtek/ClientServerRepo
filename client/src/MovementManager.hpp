#ifndef MOVEMENT_MANAGER_HPP_
#define MOVEMENT_MANAGER_HPP_

#include "IMovementManager.hpp"
#include "IKeyboardController.hpp"
#include "model/IObjectsFacade.hpp"

class MovementManager : public IMovementManager
{
public:
    MovementManager(model::ObjectsFacadePtr objectFacade);

    virtual void singleTickMove(const IKeyboardController::KeyDirection& direction);

private:
    model::ObjectsFacadePtr objectFacade_;
};

#endif  // MOVEMENT_MANAGER_HPP_
