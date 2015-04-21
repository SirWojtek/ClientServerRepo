#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

#include "client/src/CommunicationService.hpp"
#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageTypes.hpp"
#include "common/messages/MessageUtilities.hpp"

#include "TcpSocketMock.hpp"
#include "MessageQueueMock.hpp"
#include "MessageCommanderMock.hpp"

#include "utilities/CommunicationServiceSutBuilder.hpp"

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
    {
        UpdatePlayer updatePlayer;
        message_ = std::make_shared<std::string>(getMessageJson(updatePlayer));
        messageType_ = messagetype::UpdatePlayer;
    }

    void insertMessageIntoCommonicationServiceMultiMap()
    {
        getMessageOfTypeAfterInsert(messagetype::UpdateEnvironment, message_);
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

        auto ret = communicationServ_->getMessage(type, true);

        return ret;
    }

    TcpSocketMockPtr tcpSocketMock_;
    MessageQueueMockPtr writerQueueMock_;
    MessageQueueMockPtr readerQueueMock_;
    MessageCommanderMockPtr messageWriterMock_;
    MessageCommanderMockPtr messageReaderMock_;
    CommunicationServicePtr communicationServ_;

    std::shared_ptr<std::string> message_;
    messagetype::MessageType messageType_;
    std::string host = "127.0.0.1";
    std::string port = "4001";  // from implementation
};

TEST_F(CommunicationServiceShould, prepareCommunicationSocket)
{
    EXPECT_CALL(*tcpSocketMock_, connect(host, port));
    EXPECT_CALL(*messageWriterMock_, start())
        .WillOnce(Return(nullptr));
    EXPECT_CALL(*messageReaderMock_, start())
        .WillOnce(Return(nullptr));

    communicationServ_->startService();
}

TEST_F(CommunicationServiceShould, putUpdatePlayerMessageInQueueAndGetOkResponse)
{
    UpdatePlayer msg;
    OkResponse ok;

    EXPECT_CALL(*writerQueueMock_, pushMessage(_));
    EXPECT_CALL(*readerQueueMock_, popMessage())
        .WillOnce(Return(std::make_shared<std::string>(getMessageJson(ok))));

    ASSERT_EQ(communicationServ_->putMessageInQueue(msg), ok);
}

TEST_F(CommunicationServiceShould, putUpdatePlayerMessageInQueueAndNotGetOkResponseThrows)
{
    UpdatePlayer msg;

    EXPECT_CALL(*writerQueueMock_, pushMessage(_));
    EXPECT_CALL(*readerQueueMock_, popMessage())
        .WillRepeatedly(Return(nullptr));

    EXPECT_THROW(communicationServ_->putMessageInQueue(msg), std::runtime_error);
}

TEST_F(CommunicationServiceShould, returnNullPtrIfCannotGetMessageOfType)
{
    auto rec = getMessageOfTypeAfterInsert(messagetype::UpdateEnvironment, message_);

    ASSERT_EQ(rec, nullptr);
}

TEST_F(CommunicationServiceShould, getMessageOfTypeIfIsNotInQueue)
{
    auto rec = getMessageOfTypeAfterInsert(messageType_, message_);

    ASSERT_EQ(*rec, *message_);
}

TEST_F(CommunicationServiceShould, getMessageOfTypeIfIsInQueue)
{
    insertMessageIntoCommonicationServiceMultiMap();

    auto rec = communicationServ_->getMessage(messageType_, false);

    ASSERT_EQ(*message_, *rec);
}


