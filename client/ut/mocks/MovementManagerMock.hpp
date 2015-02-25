#ifndef MOVEMENT_MANAGER_MOCK_HPP_
#define MOVEMENT_MANAGER_MOCK_HPP_

#include <gmock/gmock.h>
#include <memory>

#include "client/src/IKeyboardController.hpp"
#include "client/src/IMovementManager.hpp"

class MovementManagerMock : public IMovementManager
{
public:
    MOCK_METHOD1(singleTickMove, void(const IKeyboardController::KeyDirection& direction));
};
using MovementManagerMockPtr = std::shared_ptr<MovementManagerMock>;

#endif  // MOVEMENT_MANAGER_MOCK_HPP_
