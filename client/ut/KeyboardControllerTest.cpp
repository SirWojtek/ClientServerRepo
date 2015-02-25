#include <gtest/gtest.h>
#include <memory>

#include "client/src/KeyboardController.hpp"

#include "KeyGetterMock.hpp"

using namespace ::testing;

struct Params
{
    char key;
    KeyboardController::KeyDirection direction;
};

class KeyboardControllerShould : public TestWithParam<Params>
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
    Params param = GetParam();

    EXPECT_CALL(*keyGetterMock_, getPressedKey())
        .WillOnce(Return(param.key));

    EXPECT_EQ(keyboardController_->getKeyboardInput(), param.direction);
    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), false);
}

INSTANTIATE_TEST_CASE_P(keyCombinations, KeyboardControllerShould, Values(
        Params({'w', KeyboardController::Up}),
        Params({'s', KeyboardController::Down}),
        Params({'d', KeyboardController::Right}),
        Params({'a', KeyboardController::Left}),
        Params({'j', KeyboardController::None})
));

TEST_F(KeyboardControllerShould, returnTrueIfExitKeyWasPressed)
{
    EXPECT_CALL(*keyGetterMock_, getPressedKey())
        .WillOnce(Return('q'));

    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), false);
    EXPECT_EQ(keyboardController_->getKeyboardInput(), KeyboardController::None);
    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), true);
}
