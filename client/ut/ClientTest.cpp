#include <gtest/gtest.h>
#include <memory>

#include "client/src/Client.hpp"
#include "CommunicationServiceMock.hpp"
#include "KeyboardControllerMock.hpp"

using namespace ::testing;

class ClientShould : public ::testing::Test
{
protected:
    ClientShould() :
        communicationServMock_(std::make_shared<CommunicationServiceMock>()),
        keyboardControllerMock_(std::make_shared<KeyboardControllerMock>()),
        client_(std::make_shared<Client>(communicationServMock_, keyboardControllerMock_))
    {}

    void SetUp()
    {
        EXPECT_CALL(*communicationServMock_, startService(host, port));
        EXPECT_CALL(*communicationServMock_, tearDown());
    }

    CommunicationServiceMockPtr communicationServMock_;
    KeyboardControllerMockPtr keyboardControllerMock_;
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
    const unsigned loops = 5;

    Expectation inputExpect =
    EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
        .Times(loops)
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*keyboardControllerMock_, getKeyboardInput())
        .Times(loops)
        .WillRepeatedly(Return(KeyboardControllerMock::None));
    EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
        .After(inputExpect)
        .WillOnce(Return(true));

    EXPECT_EQ(0, client_->start(0, nullptr));
}

TEST_F(ClientShould, catchThrowedException)
{
    EXPECT_CALL(*keyboardControllerMock_, wasExitKeyPressed())
        .WillOnce(Throw(std::runtime_error("Error")));
    EXPECT_NO_THROW(client_->start(0, nullptr));
}
