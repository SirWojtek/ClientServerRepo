#include <memory>
#include <string>
#include <stdexcept>

#include <gtest/gtest.h>

#include "MessageQueueMock.hpp"
#include "TcpSocketMock.hpp"
#include "client/src/MessageWriter.hpp"

using namespace ::testing;

class MessageWriterShould : public ::testing::Test
{
protected:
    MessageWriterShould() :
        tcpSocketMock_(std::make_shared<TcpSocketMock>()),
        messageQueueMock_(std::make_shared<MessageQueueMock>()),
        messageWriter_(std::make_shared<MessageWriter>(tcpSocketMock_, messageQueueMock_))
    {}

    TcpSocketMockPtr tcpSocketMock_;
    MessageQueueMockPtr messageQueueMock_;
    MessageCommanderPtr messageWriter_;
    std::shared_ptr<std::string> message_ = std::make_shared<std::string>("test message");
};

TEST_F(MessageWriterShould, exitWhenStopFunctionWasCalled)
{
    ThreadPtr writerThread;

    EXPECT_CALL(*messageQueueMock_, popMessage())
        .WillOnce(Return(nullptr));

    messageWriter_->stop();
    writerThread = messageWriter_->start();

    writerThread->join();
}

TEST_F(MessageWriterShould, catchThrowedExceptionAndExit)
{
    ThreadPtr writerThread;

    EXPECT_CALL(*messageQueueMock_, popMessage())
        .WillOnce(Return(message_));
    EXPECT_CALL(*tcpSocketMock_, write(*message_))
        .WillOnce(Throw(std::runtime_error("error")));

    EXPECT_NO_THROW((writerThread = messageWriter_->start()));

    writerThread->join();
}

TEST_F(MessageWriterShould, sendMessageWhenItIsInQueue)
{
    ThreadPtr writerThread;
    auto msg = std::make_shared<const std::string>("test message");

    EXPECT_CALL(*messageQueueMock_, popMessage())
        .WillOnce(Return(message_));
    EXPECT_CALL(*tcpSocketMock_, write(*message_));

    messageWriter_->stop();
    writerThread = messageWriter_->start();

    writerThread->join();
}
