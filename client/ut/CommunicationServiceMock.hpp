#pragma once

#include <gmock/gmock.h>
#include <memory>

#include "ICommunicationService.hpp"

class CommunicationServiceMock : public ICommunicationService
{
public:
	MOCK_METHOD0(startService, void());
};
typedef std::shared_ptr<CommunicationServiceMock> CommunicationServiceMockPtr;
