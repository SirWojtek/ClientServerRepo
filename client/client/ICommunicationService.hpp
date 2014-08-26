#pragma once

#include <memory>

class ICommunicationService
{
public:
	virtual ~ICommunicationService() {}
	virtual void startService(const std::string& host,
		const std::string& port) = 0;
};
typedef std::shared_ptr<ICommunicationService> CommunicationServicePtr;
