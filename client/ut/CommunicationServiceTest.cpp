#include <gtest/gtest.h>
#include <memory>
#include <exception>

#include "CommunicationService.hpp"
#include "TcpSocketMock.hpp"
#include "MessageQueueMock.hpp"
#include "MessageActorMock.hpp"

using namespace ::testing;

class CommunicationServiceShould : public ::testing::Test
{
protected:
	CommunicationServiceShould() :
		tcpSocketMock_(std::make_shared<TcpSocketMock>()),
		messageQueueMock_(std::make_shared<MessageQueueMock>()),
		messageActorMock_(std::make_shared<MessageActorMock>())
	{
		communicationServ_ = std::make_shared<CommunicationService>(
			tcpSocketMock_, messageQueueMock_, messageActorMock_);
	}

	CommunicationServicePtr communicationServ_;
	TcpSocketMockPtr tcpSocketMock_;
	MessageQueueMockPtr messageQueueMock_;
	MessageActorMockPtr messageActorMock_;

	std::string host = "localhost";
	std::string port = "666";
};

TEST_F(CommunicationServiceShould, prepareCommunicationSocket)
{
	EXPECT_CALL(*tcpSocketMock_, connect(host, port));
	communicationServ_->startService(host, port);
}

TEST_F(CommunicationServiceShould, catchExceptionThrownInSocket)
{
	EXPECT_CALL(*tcpSocketMock_, connect(host, port))
		.WillOnce(Throw(std::runtime_error("Error")));
	EXPECT_NO_THROW(communicationServ_->startService(host, port));
}
