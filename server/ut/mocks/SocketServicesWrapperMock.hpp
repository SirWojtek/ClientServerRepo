#ifndef SOCKET_SERVICES_WRAPPER_MOCK_HPP_
#define SOCKET_SERVICES_WRAPPER_MOCK_HPP_

#include <gmock/gmock.h>
#include "server/src/ISocketServicesWrapper.hpp"

class SocketServicesWrapperMock : public ISocketServicesWrapper
{
public:
	MOCK_METHOD2(createReaderForQueue, void(std::shared_ptr<IBoostWrapper> boostWrapper,
		int socketNumber));
	MOCK_METHOD2(createWriterForQueue, void(std::shared_ptr<IBoostWrapper> boostWrapper,
		int socketNumber));
	MOCK_METHOD0(startCommander, std::shared_ptr<std::thread>());
	MOCK_METHOD0(stopCommander, void());

	MOCK_METHOD1(pushMessage, void(const std::string& message));
	MOCK_METHOD0(popMessage, std::shared_ptr<std::string>());
	MOCK_METHOD0(waitForEmptyQueue, void());
	MOCK_METHOD0(waitForEmptyQueueWithTimeout, void());
};

#endif