#ifndef I_SOCKET_SERVICES_WRAPPER_HPP_
#define I_SOCKET_SERVICES_WRAPPER_HPP_

#include <thread>

#include "IBoostWrapper.hpp"

class ISocketServicesWrapper
{
public:
	virtual void createQueue() = 0;
	virtual void createReaderForQueue(std::shared_ptr<IBoostWrapper> boostWrapper,
		int socketNumber) = 0;
	virtual void createWriterForQueue(std::shared_ptr<IBoostWrapper> boostWrapper,
		int socketNumber) = 0;
	virtual std::shared_ptr<std::thread> startCommander() = 0;

	virtual void pushMessage(const std::string& message) = 0;
	virtual std::shared_ptr<std::string> popMessage() = 0;
	virtual void waitForEmptyQueue() = 0;
    virtual void waitForEmptyQueueWithTimeout() = 0;
};

#endif