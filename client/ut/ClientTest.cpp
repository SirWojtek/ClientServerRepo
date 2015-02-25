#include <gtest/gtest.h>
#include <memory>

#include "client/src/Client.hpp"
#include "CommunicationServiceMock.hpp"
#include "KeyboardControllerMock.hpp"
#include "MovementManagerMock.hpp"

using namespace ::testing;

class ClientShould : public ::testing::Test
{
protected:
    ClientShould() :
        communicationServMock_(std::make_shared<CommunicationServiceMock>()),
        keyboardControllerMock_(std::make_shared<KeyboardControllerMock>()),
        movementManagerMock_(std::make_shared<MovementManagerMock>()),
        client_(std::make_shared<Client>(communicationServMock_, keyboardControllerMock_,
            movementManagerMock_))
    {}

    void SetUp()
    {
        EXPECT_CALL(*communicationServMock_, startService(host, port));
        EXPECT_CALL(*communicationServMock_, tearDown());
    }

    void setClientLoopExpectations(unsigned loops)
    {
        Expectation inputExpect =
        EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
            .Times(loops)
            .WillRepeatedly(Return(false));
        EXPECT_CALL(*keyboardControllerMock_, getKeyboardInput())
            .Times(loops)
            .WillRepeatedly(Return(KeyboardControllerMock::None));
        EXPECT_CALL(*movementManagerMock_, singleTickMove(KeyboardControllerMock::None))
            .Times(loops);
        EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
            .After(inputExpect)
            .WillOnce(Return(true));
    }

    CommunicationServiceMockPtr communicationServMock_;
    KeyboardControllerMockPtr keyboardControllerMock_;
    MovementManagerMockPtr movementManagerMock_;
    ClientPtr client_;

    std::string host = "127.0.0.1";  // static from Client.cpp
    std::string port = "4001";  // static from Client.cpp

};

TEST_F(ClientShould, ExitWhenExitKeyWasPressed)
{
    EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
        .WillOnce(Return(true));

    EXPECT_EQ(0, client_->start(0, nullptr));
}

TEST_F(ClientShould, GetKeyboardInputWhenNoExitKeyWasPressed)
{
    setClientLoopExpectations(5);

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
