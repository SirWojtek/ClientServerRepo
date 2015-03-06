#include <gtest/gtest.h>
#include <memory>

#include "client/src/Client.hpp"
#include "WorldUpdaterMock.hpp"
#include "KeyboardControllerMock.hpp"
#include "MovementManagerMock.hpp"
#include "GameWindowMock.hpp"

using namespace ::testing;

class ClientShould : public ::testing::Test
{
protected:
    ClientShould() :
        keyboardControllerMock_(std::make_shared<KeyboardControllerMock>()),
        movementManagerMock_(std::make_shared<MovementManagerMock>()),
        worldUpdaterMock_(std::make_shared<WorldUpdaterMock>()),
        gameWindowMock_(std::make_shared<GameWindowMock>()),
        client_(std::make_shared<Client>(keyboardControllerMock_,
            movementManagerMock_, worldUpdaterMock_, gameWindowMock_))
    {}

    void SetUp()
    {
        EXPECT_CALL(*worldUpdaterMock_, init());
        EXPECT_CALL(*gameWindowMock_, startWindowThread());
        EXPECT_CALL(*gameWindowMock_, tearDown());
    }

    void setClientLoopExpectations(unsigned loops,
        KeyboardControllerMock::KeyDirection direction, bool isModelUpdated)
    {
        Expectation inputExpect =
        EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
            .Times(loops)
            .WillRepeatedly(Return(false));
        EXPECT_CALL(*keyboardControllerMock_, getKeyboardInput())
            .Times(loops)
            .WillRepeatedly(Return(direction));
        EXPECT_CALL(*movementManagerMock_, singleTickMove(direction))
            .Times(loops);
        EXPECT_CALL(*worldUpdaterMock_, updateModel(isModelUpdated))
            .Times(loops);

        EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
            .After(inputExpect)
            .WillOnce(Return(true));
    }

    KeyboardControllerMockPtr keyboardControllerMock_;
    MovementManagerMockPtr movementManagerMock_;
    WorldUpdaterMockPtr worldUpdaterMock_;
    GameWindowMockPtr gameWindowMock_;
    ClientPtr client_;
};

TEST_F(ClientShould, ExitWhenExitKeyWasPressed)
{
    EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
        .WillOnce(Return(true));

    EXPECT_EQ(0, client_->start(0, nullptr));
}

TEST_F(ClientShould, GetKeyboardInputWhenNoExitKeyWasPressedAndNotUpdateModel)
{
    setClientLoopExpectations(5, KeyboardControllerMock::None, false);

    EXPECT_EQ(0, client_->start(0, nullptr));
}

TEST_F(ClientShould, GetKeyboardInputWhenNoExitKeyWasPressedAndUpdateModel)
{
    setClientLoopExpectations(5, KeyboardControllerMock::Left, true);

    EXPECT_EQ(0, client_->start(0, nullptr));
}

TEST_F(ClientShould, catchThrowedException)
{
    int returnCode = 0;

    EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
        .WillOnce(Throw(std::runtime_error("Error")));
    EXPECT_NO_THROW((returnCode = client_->start(0, nullptr)));
    EXPECT_EQ(returnCode, -1);
}
