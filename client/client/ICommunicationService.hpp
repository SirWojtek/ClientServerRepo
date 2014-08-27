#pragma once

#include <memory>
#include <thread>

class ICommunicationService
{
public:
	virtual ~ICommunicationService() {}
	virtual void startService(const std::string& host,
		const std::string& port) = 0;
	virtual void putMessageInQueue(std::string&& message) = 0;
	virtual void tearDown() = 0;
};
typedef std::shared_ptr<ICommunicationService> CommunicationServicePtr;
