
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageTypes.hpp"
#include "common/messages/MessageUtilities.hpp"

#include "utilities/CommunicationServiceSutBuilder.hpp"

using namespace ::testing;
using namespace common;

class CommunicationServiceShould : public ::testing::Test
{
protected:
    CommunicationServiceShould() :
        sut(buildCommunicationServiceSut())
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
        sut.messageQueue->messageToPop = message;
        auto ret = sut.communicationServ->getMessage(type, true);
        return ret;
    }

    CommunicationServiceSut sut;

    std::shared_ptr<std::string> message_;
    messagetype::MessageType messageType_;
    std::string host = "127.0.0.1";
    std::string port = "4001";  // from implementation
};

TEST_F(CommunicationServiceShould, putUpdatePlayerMessageInQueueAndGetOkResponse)
{
    UpdatePlayer msg;
    OkResponse ok;

    sut.messageQueue->messageToPop = std::make_shared<std::string>(getMessageJson(ok));

    ASSERT_EQ(sut.communicationServ->putMessageInQueue(msg), ok);
}

TEST_F(CommunicationServiceShould, putUpdatePlayerMessageInQueueAndNotGetOkResponseThrows)
{
    UpdatePlayer msg;

    EXPECT_THROW(sut.communicationServ->putMessageInQueue(msg), std::runtime_error);
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

    auto rec = sut.communicationServ->getMessage(messageType_, false);

    ASSERT_EQ(*message_, *rec);
}


