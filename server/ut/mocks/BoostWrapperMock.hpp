#ifndef BOOST_WRAPPER_MOCK_HPP_
#define BOOST_WRAPPER_MOCK_HPP_

#include <gmock/gmock.h>
#include "server/src/IBoostWrapper.hpp"

class BoostWrapperMock : public IBoostWrapper
{
public:
	MOCK_METHOD2(connect, void(const std::string&, const std::string&));
	MOCK_METHOD0(cancellAllAsyncServices, void());
	MOCK_METHOD0(createAcceptor, void());
	MOCK_METHOD0(createIoService, void());
	MOCK_METHOD0(addSocket, void());
	MOCK_METHOD0(getLatestSocketNumber, int());
	MOCK_METHOD3(startAccepting, void(IServerSession& session, IServerInitializer* instance,
		int socketNumber));
	MOCK_METHOD0(runIoService, void());
	MOCK_METHOD0(resetIoService, void());
	MOCK_METHOD0(stopIoService, void());
	MOCK_METHOD1(write, void(std::string& message));
	MOCK_METHOD2(write, void(std::string& message, int socketNumber));
	MOCK_METHOD1(write, void(const char* message));
	MOCK_METHOD0(read, std::shared_ptr<const std::string>());
	MOCK_METHOD1(read, std::shared_ptr<const std::string>(int socketNumber));
};

#endif