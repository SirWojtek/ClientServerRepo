#pragma once

#include <memory>
#include <thread>

#include "NetworkMessage.hpp"

class ICommunicationService
{
public:
	virtual ~ICommunicationService() {}
	virtual void startService(const std::string& host,
		const std::string& port) = 0;
	virtual void putMessageInQueue(NetworkMessage&& message) = 0;
	virtual void putMessageInQueue(const NetworkMessage& message) = 0;
	virtual void tearDown() = 0;
};
typedef std::shared_ptr<ICommunicationService> CommunicationServicePtr;
