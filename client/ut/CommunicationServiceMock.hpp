#pragma once

#include <gmock/gmock.h>
#include <memory>

#include "ICommunicationService.hpp"

class CommunicationServiceMock : public ICommunicationService
{
public:
	MOCK_METHOD2(startService, void(const std::string& host, const std::string& port));
};
typedef std::shared_ptr<CommunicationServiceMock> CommunicationServiceMockPtr;
