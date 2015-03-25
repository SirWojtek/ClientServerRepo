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

TEST_F(ServerSessionShould, Dummy)
{
	ASSERT_EQ(2, 2);
}
