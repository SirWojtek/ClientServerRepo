#ifndef MESSAGE_QUEUE_TEST_HPP_
#define MESSAGE_QUEUE_TEST_HPP_

#include <string>
#include <memory>
#include <thread>

#include <gtest/gtest.h>

#include "client/src/MessageQueue.hpp"

using namespace ::testing;

class MessageQueueShould : public ::testing::Test
{
protected:
    MessageQueueShould() {}

    MessageQueuePtr messageQueue_ = std::make_shared<MessageQueue>();
    std::string message1_ = "Test message1";
    std::string message2_ = "Test message2";
};

TEST_F(MessageQueueShould, returnNullPtrWhenNoMessageAvaible)
{
    auto msg = messageQueue_->popMessage();

    ASSERT_EQ(msg, nullptr);
}

TEST_F(MessageQueueShould, returnPushedMessage)
{
    messageQueue_->pushMessage(message1_);

    auto msg = messageQueue_->popMessage();

    ASSERT_EQ(*msg, message1_);
}

TEST_F(MessageQueueShould, returnPushedMessagesInOrder)
{
    messageQueue_->pushMessage(message1_);
    messageQueue_->pushMessage(message2_);

    auto msg1 = messageQueue_->popMessage();
    auto msg2 = messageQueue_->popMessage();

    ASSERT_EQ(*msg1, message1_);
    ASSERT_EQ(*msg2, message2_);
}

TEST_F(MessageQueueShould, waitUntilNoMessagesInQueue)
{
    messageQueue_->pushMessage(message1_);
    bool isThreadWaiting = true;

    std::thread waitingThread([this, &isThreadWaiting](void)
        {
            messageQueue_->waitForEmptyQueue();
            isThreadWaiting = false;
        });

    ASSERT_EQ(isThreadWaiting, true);

    messageQueue_->popMessage();
    waitingThread.join();

    ASSERT_EQ(isThreadWaiting, false);
}

#endif  // MESSAGE_QUEUE_TEST_HPP_