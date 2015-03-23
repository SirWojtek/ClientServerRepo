#ifndef SOCKET_SERVICES_WRAPPER_HPP_
#define SOCKET_SERVICES_WRAPPER_HPP_

#include "common/utilities/Console.hpp"
#include "ISocketServicesWrapper.hpp"
#include "common/socketServices/IMessageQueue.hpp"
#include "common/socketServices/IMessageCommander.hpp"

class SocketServicesWrapper : public ISocketServicesWrapper
{
public:
	SocketServicesWrapper() :
	console_("SocketServicesWrapper")
	{ }

	void createQueue();
	void createReaderForQueue(std::shared_ptr<IBoostWrapper> boostWrapper, int socketNumber);
	void createWriterForQueue(std::shared_ptr<IBoostWrapper> boostWrapper, int socketNumber);
	std::shared_ptr<std::thread> startReader();
	std::shared_ptr<std::thread> startWriter();

	void pushMessage(const std::string& message);
	std::shared_ptr<std::string> popMessage();
	void waitForEmptyQueue();
    void waitForEmptyQueueWithTimeout();
private:
	bool commanderAlreadyExists();

	MessageQueuePtr queue_;
	MessageCommanderPtr commander_;
	Console console_;
};

#endif