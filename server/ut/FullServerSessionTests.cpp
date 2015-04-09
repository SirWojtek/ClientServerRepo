#include "mocks/BoostWrapperMock.hpp"
#include "mocks/SocketServicesWrapperMock.hpp"
#include "server/src/ServerSession.hpp"

#include "common/messages/MessageUtilities.hpp"

using namespace ::testing;

void dummyThreadFunction()
{
    return;
}

class ServerSessionShould : public ::testing::Test
{
protected:
    ServerSessionShould() :
    boostWrapperMock_(std::make_shared<BoostWrapperMock>()),
    readerMock_(std::make_shared<SocketServicesWrapperMock>()),
    writerMock_(std::make_shared<SocketServicesWrapperMock>()),
    serverSession_(std::make_shared<ServerSession>(boostWrapperMock_, readerMock_, writerMock_, 1))
    {
        serverSession_->makeDatabaseConnection(std::string("test_db"));
    }

    void setStartSessionExpectations()
    {
        EXPECT_CALL(*readerMock_, createReaderForQueue(_, _));
        EXPECT_CALL(*writerMock_, createWriterForQueue(_, _));

        EXPECT_CALL(*readerMock_, startCommander())
            .WillOnce(Return(std::make_shared<std::thread>(::dummyThreadFunction)));
        EXPECT_CALL(*writerMock_, startCommander())
            .WillOnce(Return(std::make_shared<std::thread>(::dummyThreadFunction)));
    }

    void setTearDownExpectations()
    {
        EXPECT_CALL(*readerMock_, stopCommander());
        EXPECT_CALL(*writerMock_, waitForEmptyQueue());
        EXPECT_CALL(*writerMock_, stopCommander());
    }

    std::shared_ptr<BoostWrapperMock> boostWrapperMock_;
    std::shared_ptr<SocketServicesWrapperMock> readerMock_;
    std::shared_ptr<SocketServicesWrapperMock> writerMock_;
    std::shared_ptr<ServerSession> serverSession_;
};

TEST_F(ServerSessionShould, StartAndStopServicesWhenClientNotLogged)
{
    setStartSessionExpectations();

    EXPECT_CALL(*readerMock_, popMessage())
        .WillOnce(Return(std::shared_ptr<std::string>()));

    setTearDownExpectations();

    serverSession_->startThreadsAndRun(serverSession_);
}

TEST_F(ServerSessionShould, StartAndStopServicesWhenLogoutSignalOccurs)
{
    common::Login loginMessage;
    loginMessage.playerName = "Gettor";
    std::string json = common::getMessageJson<common::Login>(loginMessage);

    common::Logout logoutMessage;
    std::string json2 = common::getMessageJson<common::Logout>(logoutMessage);

    common::OkResponse okMessage;
    okMessage.serverAllows = true;;
    std::string json3 = common::getMessageJson<common::OkResponse>(okMessage);

    setStartSessionExpectations();

    EXPECT_CALL(*readerMock_, popMessage())
        .WillOnce(Return(std::make_shared<std::string>(json)))
        .WillOnce(Return(std::make_shared<std::string>(json2)));

    EXPECT_CALL(*writerMock_, pushMessage(json3));
    EXPECT_CALL(*writerMock_, waitForEmptyQueueWithTimeout());

    setTearDownExpectations();

    serverSession_->startThreadsAndRun(serverSession_);
}

TEST_F(ServerSessionShould, KeepReceivedMessagesVectorAtMaximumSize)
{
    for (int i=0; i<150; i++)
    {
        std::shared_ptr<std::string> messageString =
            std::make_shared<std::string>(std::to_string(i));
        serverSession_->cyclicPushReceivedMessages(common::messagetype::OkResponse, messageString);
    }
    ASSERT_EQ(serverSession_->getMessagePairVector().size(), 100);
    ASSERT_EQ(*(serverSession_->getMessagePairVector()[99].second), "149");
}

TEST_F(ServerSessionShould, KeepTrackOfMessageTypesAmount)
{
    std::shared_ptr<std::string> messageString = std::make_shared<std::string>("Dummy");
    for (int i=0; i<50; i++)
    {
        serverSession_->cyclicPushReceivedMessages(common::messagetype::OkResponse, messageString);
    }
    for (int i=0; i<20; i++)
    {
        serverSession_->cyclicPushReceivedMessages(common::messagetype::Login, messageString);
    }
    for (int i=0; i<30; i++)
    {
        serverSession_->cyclicPushReceivedMessages(common::messagetype::UpdateEnvironment,
            messageString);
    }
    auto counter = serverSession_->getMessageCounter();
    ASSERT_EQ(counter[common::messagetype::OkResponse], 50);
    ASSERT_EQ(counter[common::messagetype::Login], 20);
    ASSERT_EQ(counter[common::messagetype::UpdateEnvironment], 30);
}

TEST_F(ServerSessionShould, ValidateUserLoginWithCorrectLogin)
{
    common::Login loginMessage;
    loginMessage.playerName = "Gettor";
    std::string json = common::getMessageJson<common::Login>(loginMessage);

    common::OkResponse okMessage;
    okMessage.serverAllows = true;;
    std::string json2 = common::getMessageJson<common::OkResponse>(okMessage);

    EXPECT_CALL(*readerMock_, popMessage())
        .WillOnce(Return(std::make_shared<std::string>(json)));

    EXPECT_CALL(*writerMock_, pushMessage(json2));

    ASSERT_TRUE(serverSession_->wasClientLoggedInCorrectly());
}

TEST_F(ServerSessionShould, ValidateUserLoginWithIncorrectLogin)
{
    common::Login loginMessage;
    loginMessage.playerName = "Gettor69857498";
    std::string json = common::getMessageJson<common::Login>(loginMessage);

    common::OkResponse okMessage;
    okMessage.serverAllows = false;;
    std::string json2 = common::getMessageJson<common::OkResponse>(okMessage);

    EXPECT_CALL(*readerMock_, popMessage())
        .WillOnce(Return(std::make_shared<std::string>(json)));

    EXPECT_CALL(*writerMock_, pushMessage(json2));
    
    ASSERT_TRUE(!serverSession_->wasClientLoggedInCorrectly());
}