#include <gtest/gtest.h>
#include <memory>

#include "client/src/MovementManager.hpp"

#include "ObjectsFacadeMock.hpp"

#include "client/src/IKeyboardController.hpp"
#include "client/src/model/objects/Object.hpp"

using namespace ::testing;

struct DirectionToPosition
{
    IKeyboardController::KeyDirection direction;
    model::Object::Position oldPosition;
    model::Object::Position newPosition;
};

class MovementManagerShould : public TestWithParam<DirectionToPosition>
{
protected:
    MovementManagerShould() :
        objectsFacadeMock_(std::make_shared<ObjectsFacadeMock>()),
        movementManager_(std::make_shared<MovementManager>(objectsFacadeMock_))
    {}


    ObjectsFacadeMockPtr objectsFacadeMock_;
    MovementManagerPtr movementManager_;
};

TEST_P(MovementManagerShould, changePlayerPosition)
{
    DirectionToPosition param = GetParam();
    model::ObjectPtr player = std::make_shared<model::Object>(param.oldPosition);

    EXPECT_CALL(*objectsFacadeMock_, getPlayerObject())
        .WillOnce(Return(player));

    movementManager_->singleTickMove(param.direction);

    EXPECT_EQ(player->position, param.newPosition);
}

INSTANTIATE_TEST_CASE_P(playerPossibleMoves, MovementManagerShould, Values(
        DirectionToPosition({IKeyboardController::Up,
            {MovementManager::delta, MovementManager::delta},
            {MovementManager::delta, 0} }),
        DirectionToPosition({IKeyboardController::Down,
            {MovementManager::delta, MovementManager::delta},
            {MovementManager::delta, MovementManager::delta + MovementManager::delta} }),
        DirectionToPosition({IKeyboardController::Right,
            {MovementManager::delta, MovementManager::delta},
            {MovementManager::delta + MovementManager::delta, MovementManager::delta} }),
        DirectionToPosition({IKeyboardController::Left,
            {MovementManager::delta, MovementManager::delta},
            {0, MovementManager::delta} }),
        DirectionToPosition({IKeyboardController::Up,
            {0, 0},
            {0, 0} }),
        DirectionToPosition({IKeyboardController::Down,
            {0, 0},
            {0, MovementManager::delta} }),
        DirectionToPosition({IKeyboardController::Right,
            {0, 0},
            {MovementManager::delta, 0} }),
        DirectionToPosition({IKeyboardController::Left,
            {0, 0},
            {0, 0} })));

TEST_F(MovementManagerShould, doNothingWhenReceiveNoneDirection)
{
    movementManager_->singleTickMove(IKeyboardController::None);
}