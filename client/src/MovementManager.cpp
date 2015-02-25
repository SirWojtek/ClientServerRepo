
#include "MovementManager.hpp"

#include "IKeyboardController.hpp"
#include "model/IObjectsFacade.hpp"

MovementManager::MovementManager(model::ObjectsFacadePtr objectFacade) :
    objectFacade_(objectFacade) {}

void MovementManager::singleTickMove(const IKeyboardController::KeyDirection& direction)
{

}
