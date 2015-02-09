#include <gtest/gtest.h>
#include <memory>
#include <exception>

#include "CommunicationService.hpp"
#include "TcpSocketMock.hpp"
#include "MessageQueueMock.hpp"
#include "MessageWriterMock.hpp"
#include "NetworkMessage.hpp"

using namespace ::testing;

class CommunicationServiceShould : public ::testing::Test
{
protected:
	CommunicationServiceShould() :
		tcpSocketMock_(std::make_shared<TcpSocketMock>()),
		messageQueueMock_(std::make_shared<MessageQueueMock>()),
		messageWriterMock_(std::make_shared<MessageWriterMock>()),
		communicationServ_(std::make_shared<CommunicationService>(
			tcpSocketMock_, messageQueueMock_, messageWriterMock_))
	{}

	TcpSocketMockPtr tcpSocketMock_;
	MessageQueueMockPtr messageQueueMock_;
	MessageWriterMockPtr messageWriterMock_;
	CommunicationServicePtr communicationServ_;

	std::string host = "localhost";
	std::string port = "666";
};

TEST_F(CommunicationServiceShould, prepareCommunicationSocket)
{
	EXPECT_CALL(*tcpSocketMock_, connect(host, port));
	EXPECT_CALL(*messageWriterMock_, start())
		.WillOnce(Return(nullptr));

	communicationServ_->startService(host, port);
}

TEST_F(CommunicationServiceShould, putMessageInQueue)
{
	NetworkMessage msg = { "test", nullptr };

	EXPECT_CALL(*messageQueueMock_, pushMessage(msg));

	communicationServ_->putMessageInQueue(msg);
}
