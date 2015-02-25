#ifndef IMOVEMENT_MANAGER_HPP_
#define IMOVEMENT_MANAGER_HPP_

#include "IKeyboardController.hpp"
#include <memory>

class IMovementManager
{
public:
    virtual void singleTickMove(const IKeyboardController::KeyDirection& direction) = 0;
};
using MovementManagerPtr = std::shared_ptr<IMovementManager>;

#endif  // IMOVEMENT_MANAGER_HPP_
