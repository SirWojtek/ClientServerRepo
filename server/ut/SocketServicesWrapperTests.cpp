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
    {
        socketServicesWrapper_->createReaderForQueue(boostWrapperMock_, 0);
    }

    std::shared_ptr<BoostWrapperMock> boostWrapperMock_;
    std::shared_ptr<MessageQueueMock> messageQueueMock_;
    std::shared_ptr<SocketServicesWrapper> socketServicesWrapper_;
};

TEST_F(SocketServicesWrapperShould, pushMessageOntoQueue)
{
    EXPECT_CALL(*messageQueueMock_, pushMessage(_));
    socketServicesWrapper_->pushMessage("AnyString");
}

TEST_F(SocketServicesWrapperShould, pop)
{
    EXPECT_CALL(*messageQueueMock_, popMessage())
        .WillOnce(Return(std::make_shared<std::string>("AnyString")));
    auto retValue = socketServicesWrapper_->popMessage();
    EXPECT_EQ(*retValue, "AnyString");
}

TEST_F(SocketServicesWrapperShould, waitForEmptyQueue)
{
    EXPECT_CALL(*messageQueueMock_, waitForEmptyQueue());
    socketServicesWrapper_->waitForEmptyQueue();
}

TEST_F(SocketServicesWrapperShould, waitForEmptyQueueWithTimeout)
{
    EXPECT_CALL(*messageQueueMock_, waitForEmptyQueueWithTimeout());
    socketServicesWrapper_->waitForEmptyQueueWithTimeout();
}