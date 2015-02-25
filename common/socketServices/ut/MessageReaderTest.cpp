#include <memory>
#include <string>
#include <stdexcept>

#include <gtest/gtest.h>

#include "MessageQueueMock.hpp"
#include "TcpSocketMock.hpp"
#include "common/socketServices/MessageReader.hpp"

using namespace ::testing;

class MessageReaderShould : public ::testing::Test
{
protected:
    MessageReaderShould() :
        tcpSocketMock_(std::make_shared<TcpSocketMock>()),
        messageQueueMock_(std::make_shared<MessageQueueMock>()),
        messageReader_(std::make_shared<MessageReader>(tcpSocketMock_, messageQueueMock_))
    {}

    TcpSocketMockPtr tcpSocketMock_;
    MessageQueueMockPtr messageQueueMock_;
    MessageCommanderPtr messageReader_;
};

TEST_F(MessageReaderShould, catchThrowedExceptionAndExit)
{
    ThreadPtr readerThread;

    EXPECT_CALL(*tcpSocketMock_, read())
        .WillOnce(Throw(std::runtime_error("error")));

    EXPECT_NO_THROW((readerThread = messageReader_->start()));

    readerThread->join();
}

TEST_F(MessageReaderShould, exitWhenStopFunctionWasCalled)
{
    ThreadPtr readerThread;

    EXPECT_CALL(*tcpSocketMock_, read())
        .WillOnce(Return(nullptr));

    messageReader_->stop();
    readerThread = messageReader_->start();

    readerThread->join();
}

TEST_F(MessageReaderShould, addMessageIntoQueueWhenItArrives)
{
    ThreadPtr readerThread;
    auto msg = std::make_shared<const std::string>("test message");

    EXPECT_CALL(*tcpSocketMock_, read())
        .WillOnce(Return(msg));
    EXPECT_CALL(*messageQueueMock_, pushMessage(*msg));

    messageReader_->stop();
    readerThread = messageReader_->start();

    readerThread->join();
}
