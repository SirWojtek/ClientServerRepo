#ifndef COMMUNICATION_SERVICE_MOCK_HPP_
#define COMMUNICATION_SERVICE_MOCK_HPP_

#include <gmock/gmock.h>
#include <memory>

#include "client/src/ICommunicationService.hpp"
#include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageUtilities.hpp"

class CommunicationServiceMock : public ICommunicationService
{
public:
    MOCK_METHOD2(startService, void(const std::string& host, const std::string& port));
    MOCK_METHOD1(putMessageInQueue, void(const common::UpdatePlayer& message));
    MOCK_METHOD1(getMessage, std::shared_ptr<std::string>(
        const common::messagetype::MessageType& type));
    MOCK_METHOD0(tearDown, void());
};
typedef std::shared_ptr<CommunicationServiceMock> CommunicationServiceMockPtr;

#endif  // COMMUNICATION_SERVICE_MOCK_HPP_
