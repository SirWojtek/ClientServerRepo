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
    {}

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
