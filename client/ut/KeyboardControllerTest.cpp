#include <gtest/gtest.h>
#include <memory>

#include "client/src/KeyboardController.hpp"

#include "KeyGetterMock.hpp"

using namespace ::testing;

struct KeyToDirection
{
    char key;
    KeyboardController::KeyDirection direction;
};

class KeyboardControllerShould : public TestWithParam<KeyToDirection>
{
protected:
    KeyboardControllerShould() :
        keyGetterMock_(std::make_shared<KeyGetterMock>()),
        keyboardController_(std::make_shared<KeyboardController>(keyGetterMock_))
    {}

    KeyGetterMockPtr keyGetterMock_;
    KeyboardControllerPtr keyboardController_;
};

TEST_P(KeyboardControllerShould, returnCorrectDirection)
{
    KeyToDirection param = GetParam();

    EXPECT_CALL(*keyGetterMock_, getPressedKey())
        .WillOnce(Return(param.key));

    EXPECT_EQ(keyboardController_->getKeyboardInput(), param.direction);
    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), false);
}

INSTANTIATE_TEST_CASE_P(keyCombinations, KeyboardControllerShould, Values(
        KeyToDirection({'w', KeyboardController::Up}),
        KeyToDirection({'s', KeyboardController::Down}),
        KeyToDirection({'d', KeyboardController::Right}),
        KeyToDirection({'a', KeyboardController::Left}),
        KeyToDirection({'j', KeyboardController::None})
));

TEST_F(KeyboardControllerShould, returnTrueIfExitKeyWasPressed)
{
    EXPECT_CALL(*keyGetterMock_, getPressedKey())
        .WillOnce(Return('q'));

    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), false);
    EXPECT_EQ(keyboardController_->getKeyboardInput(), KeyboardController::None);
    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), true);
}
