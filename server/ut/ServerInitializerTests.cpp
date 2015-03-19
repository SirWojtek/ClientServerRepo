#include "mocks/BoostWrapperMock.hpp"
#include "server/src/ServerInitializer.hpp"

using namespace ::testing;

class ServerInitializerShould : public ::testing::Test
{
protected:
    ServerInitializerShould() :
    boostWrapperMock_(std::make_shared<BoostWrapperMock>())
    {}

    void SetUp()
    {
        EXPECT_CALL(*boostWrapperMock_, getLatestSocketNumber())
        	.WillOnce(Return(1));
        serverInitializer_ = std::make_shared<ServerInitializer>(boostWrapperMock_);
    }

    std::shared_ptr<BoostWrapperMock> boostWrapperMock_;
    std::shared_ptr<ServerInitializer> serverInitializer_;
};

TEST_F(ServerInitializerShould, callAcceptorService)
{
	EXPECT_CALL(*boostWrapperMock_, getLatestSocketNumber())
        	.WillOnce(Return(1));
	EXPECT_CALL(*boostWrapperMock_, startAccepting(_, _, _));
	serverInitializer_->runAsyncAccept();
}

TEST_F(ServerInitializerShould, handleAcceptCorrectly)
{
	EXPECT_CALL(*boostWrapperMock_, addSocket());
	EXPECT_CALL(*boostWrapperMock_, getLatestSocketNumber())
    	.Times(2)
    	.WillRepeatedly(Return(1));
    EXPECT_CALL(*boostWrapperMock_, startAccepting(_, _, _));	
	serverInitializer_->handleAccept(boost::system::error_code());
	serverInitializer_->joinThreads();
}