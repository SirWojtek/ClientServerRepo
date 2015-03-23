#include "mocks/BoostWrapperMock.hpp"
#include "common/socketServices/ut/mocks/MessageQueueMock.hpp"
#include "server/src/SocketServicesWrapper.hpp"

using namespace ::testing;

class SocketServicesWrapperShould : public ::testing::Test
{
protected:
    SocketServicesWrapperShould() :
    boostWrapperMock_(std::make_shared<BoostWrapperMock>()),
    messageQueueMock_(std::make_shared<MessageQueueMock>()),
    socketServicesWrapper_(std::make_shared<SocketServicesWrapper>(messageQueueMock_))
    {}

    std::shared_ptr<BoostWrapperMock> boostWrapperMock_;
    std::shared_ptr<MessageQueueMock> messageQueueMock_;
    std::shared_ptr<SocketServicesWrapper> socketServicesWrapper_;
};

TEST_F(SocketServicesWrapperShould, Dummy)
{
    ASSERT_EQ(2, 2);
}