#pragma once

#include <memory>

class ICommunicationService
{
public:
	virtual void startService() = 0;
};
typedef std::shared_ptr<ICommunicationService> CommunicationServicePtr;
