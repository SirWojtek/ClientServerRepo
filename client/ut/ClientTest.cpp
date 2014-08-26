#include <gtest/gtest.h>
#include <memory>

#include "Client.hpp"
#include "CommunicationServiceMock.hpp"

class ClientShould : public ::testing::Test
{
protected:
	ClientShould() :
		communicationServMock_(std::make_shared<CommunicationServiceMock>())
	{
		client_ = std::make_shared<Client>(communicationServMock_);
	}

	ClientPtr client_;
	CommunicationServiceMockPtr communicationServMock_;
};

TEST_F(ClientShould, PrepareApplicationComponents)
{
	std::string host = "127.0.0.1";  // static from Client.cpp
	std::string port = "1234";  // static from Client.cpp

	EXPECT_CALL(*communicationServMock_, startService(host, port));
	EXPECT_EQ(0, client_->start(0, nullptr));
}
