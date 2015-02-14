#include <gtest/gtest.h>
#include <memory>
#include <exception>

#include "client/src/CommunicationService.hpp"
#include "TcpSocketMock.hpp"
#include "MessageQueueMock.hpp"
#include "MessageCommanderMock.hpp"

using namespace ::testing;

class CommunicationServiceShould : public ::testing::Test
{
protected:
    CommunicationServiceShould() :
        tcpSocketMock_(std::make_shared<TcpSocketMock>()),
        writerQueueMock_(std::make_shared<MessageQueueMock>()),
        readerQueueMock_(std::make_shared<MessageQueueMock>()),
        messageWriterMock_(std::make_shared<MessageCommanderMock>()),
        messageReaderMock_(std::make_shared<MessageCommanderMock>()),
        communicationServ_(std::make_shared<CommunicationService>(
            tcpSocketMock_, writerQueueMock_, messageWriterMock_,
            readerQueueMock_, messageReaderMock_))
    {}

    TcpSocketMockPtr tcpSocketMock_;
    MessageQueueMockPtr writerQueueMock_;
    MessageQueueMockPtr readerQueueMock_;
    MessageCommanderMockPtr messageWriterMock_;
    MessageCommanderMockPtr messageReaderMock_;
    CommunicationServicePtr communicationServ_;

    std::string host = "localhost";
    std::string port = "666";
};

TEST_F(CommunicationServiceShould, prepareCommunicationSocket)
{
    EXPECT_CALL(*tcpSocketMock_, connect(host, port));
    EXPECT_CALL(*messageWriterMock_, start())
        .WillOnce(Return(nullptr));
    EXPECT_CALL(*messageReaderMock_, start())
        .WillOnce(Return(nullptr));

    communicationServ_->startService(host, port);
}

// TEST_F(CommunicationServiceShould, putMessageInQueue)
// {
//     NetworkMessage msg{ "test" };

//     EXPECT_CALL(*writerQueueMock_, pushMessage(msg));

//     communicationServ_->putMessageInQueue(msg);
// }
