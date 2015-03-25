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
        serverInitializer_ = std::make_shared<ServerInitializer>(boostWrapperMock_);
    }

    std::shared_ptr<BoostWrapperMock> boostWrapperMock_;
    std::shared_ptr<ServerInitializer> serverInitializer_;
};

TEST_F(ServerInitializerShould, callAcceptorService)
{
	EXPECT_CALL(*boostWrapperMock_, getLatestSocketNumber())
        	.Times(2)
            .WillRepeatedly(Return(1));
	EXPECT_CALL(*boostWrapperMock_, startAccepting(_, _, _));
	serverInitializer_->runAsyncAccept();
}

TEST_F(ServerInitializerShould, handleAcceptCorrectly)
{
	EXPECT_CALL(*boostWrapperMock_, addSocket());
	EXPECT_CALL(*boostWrapperMock_, getLatestSocketNumber())
    	.Times(4)
    	.WillRepeatedly(Return(1));
    EXPECT_CALL(*boostWrapperMock_, startAccepting(_, _, _))
        .Times(2);
    
    boost::system::error_code ec (0, boost::system::system_category ());
    serverInitializer_->runAsyncAccept();
	serverInitializer_->handleAccept(ec);
	serverInitializer_->joinThreads();
}

TEST_F(ServerInitializerShould, notHandleAcceptIfErrorOccured)
{
	EXPECT_CALL(*boostWrapperMock_, addSocket())
		.Times(0);
	EXPECT_CALL(*boostWrapperMock_, getLatestSocketNumber())
    	.Times(0);
    EXPECT_CALL(*boostWrapperMock_, startAccepting(_, _, _))
    	.Times(0);	

    boost::system::error_code ec (1, boost::system::system_category ());
	serverInitializer_->handleAccept(ec);
	serverInitializer_->joinThreads();
}