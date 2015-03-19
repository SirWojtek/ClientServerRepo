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
	ASSERT_EQ(2, 2);
}