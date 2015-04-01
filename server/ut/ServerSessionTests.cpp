#include "mocks/BoostWrapperMock.hpp"
#include "mocks/SocketServicesWrapperMock.hpp"
#include "server/src/ServerSession.hpp"

using namespace ::testing;

class ServerSessionShould : public ::testing::Test
{
protected:
    ServerSessionShould() :
    boostWrapperMock_(std::make_shared<BoostWrapperMock>()),
    readerMock_(std::make_shared<SocketServicesWrapperMock>()),
    writerMock_(std::make_shared<SocketServicesWrapperMock>()),
    serverSession_(std::make_shared<ServerSession>(boostWrapperMock_, readerMock_, writerMock_, 1))
    {}

    void SetUp()
    {
        //serverInitializer_ = std::make_shared<ServerInitializer>(boostWrapperMock_);
    }

    std::shared_ptr<BoostWrapperMock> boostWrapperMock_;
    std::shared_ptr<SocketServicesWrapperMock> readerMock_;
    std::shared_ptr<SocketServicesWrapperMock> writerMock_;
    std::shared_ptr<ServerSession> serverSession_;
};

TEST_F(ServerSessionShould, StartAndStopServicesWhenClientNotLogged)
{
    EXPECT_CALL(*readerMock_, createReaderForQueue(_, _));
    EXPECT_CALL(*writerMock_, createWriterForQueue(_, _));

	EXPECT_CALL(*readerMock_, startCommander())
        .WillOnce(Return(ThreadPtr()));
    EXPECT_CALL(*writerMock_, startCommander())
        .WillOnce(Return(ThreadPtr()));

    EXPECT_CALL(*readerMock_, popMessage())
        .WillOnce(Return(std::shared_ptr<std::string>()));

    serverSession_->startThreadsAndRun(serverSession_);
}
