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
	EXPECT_CALL(*communicationServMock_, startService()).Times(1);
	EXPECT_EQ(0, client_->start(0, nullptr));
}
