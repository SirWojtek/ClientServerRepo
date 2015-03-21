#ifndef COMMUNICATION_SERVICE_MOCK_HPP_
#define COMMUNICATION_SERVICE_MOCK_HPP_

#include <gmock/gmock.h>

#include "client/src/ICommunicationService.hpp"

class CommunicationServiceMock : public ICommunicationService
{
public:
    MOCK_METHOD0(startService, void());
    MOCK_METHOD1(putMessageInQueue, common::OkResponse(const common::UpdatePlayer& message));
    MOCK_METHOD1(putMessageInQueue, common::OkResponse(const common::Login& message));
    MOCK_METHOD2(getMessage, std::shared_ptr<std::string>(
        const common::messagetype::MessageType& type, bool wait));
    MOCK_METHOD0(tearDown, void());
};
typedef std::shared_ptr<CommunicationServiceMock> CommunicationServiceMockPtr;

#endif  // COMMUNICATION_SERVICE_MOCK_HPP_
