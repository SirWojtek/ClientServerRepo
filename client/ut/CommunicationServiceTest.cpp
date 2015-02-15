#include <gtest/gtest.h>
#include <memory>
#include <exception>

#include "client/src/CommunicationService.hpp"
#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageTypes.hpp"

#include "TcpSocketMock.hpp"
#include "MessageQueueMock.hpp"
#include "MessageCommanderMock.hpp"

using namespace ::testing;
using namespace common;

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

    void insertMessageIntoCommonicationServiceMultiMap()
    {
        getMessageOfTypeAfterInsert(messagetype::UpdatePlayer, message_);
    }

    std::shared_ptr<std::string> getMessageOfTypeAfterInsert(const messagetype::MessageType& type,
        std::shared_ptr<std::string> message)
    {
        {
            InSequence seq;
            EXPECT_CALL(*readerQueueMock_, popMessage())
                .WillOnce(Return(message));
            EXPECT_CALL(*readerQueueMock_, popMessage())
                .WillRepeatedly(Return(nullptr));
        }

        auto ret = communicationServ_->getMessage(type);

        return ret;
    }


    TcpSocketMockPtr tcpSocketMock_;
    MessageQueueMockPtr writerQueueMock_;
    MessageQueueMockPtr readerQueueMock_;
    MessageCommanderMockPtr messageWriterMock_;
    MessageCommanderMockPtr messageReaderMock_;
    CommunicationServicePtr communicationServ_;

    std::shared_ptr<std::string> message_ =
        std::make_shared<std::string>("Until getMessageType not implemented");
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

TEST_F(CommunicationServiceShould, putMessageInQueue)
{
    UpdatePlayer msg;

    EXPECT_CALL(*writerQueueMock_, pushMessage(_));

    communicationServ_->putMessageInQueue(msg);
}

TEST_F(CommunicationServiceShould, returnNullPtrIfCannotGetMessageOfType)
{
    auto rec = getMessageOfTypeAfterInsert(messagetype::UpdatePlayer, message_);

    ASSERT_EQ(rec, nullptr);
}

TEST_F(CommunicationServiceShould, getMessageOfTypeIfIsNotInQueue)
{
    auto rec = getMessageOfTypeAfterInsert(messagetype::UpdateEnvironment, message_);

    ASSERT_EQ(*rec, *message_);
}

TEST_F(CommunicationServiceShould, getMessageOfTypeIfIsInQueue)
{
    insertMessageIntoCommonicationServiceMultiMap();

    auto rec = communicationServ_->getMessage(messagetype::UpdateEnvironment);

    ASSERT_EQ(*message_, *rec);
}


