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
    model::Object::Position position;
};

const int delta = 1;

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
    model::ObjectPtr player = std::make_shared<model::Object>();

    EXPECT_CALL(*objectsFacadeMock_, getPlayerObject())
        .WillOnce(Return(player));

    movementManager_->singleTickMove(param.direction);

    EXPECT_EQ(player->position, param.position);
}

INSTANTIATE_TEST_CASE_P(playerPossibleMoves, MovementManagerShould, Values(
        DirectionToPosition({IKeyboardController::Up, {0, delta} }),
        DirectionToPosition({IKeyboardController::Down, {0, -delta} }),
        DirectionToPosition({IKeyboardController::Right, {delta, 0} }),
        DirectionToPosition({IKeyboardController::Left, {-delta, 0} })
));

TEST_F(MovementManagerShould, doNothingWhenReceiveNoneDirection)
{
    movementManager_->singleTickMove(IKeyboardController::None);
}