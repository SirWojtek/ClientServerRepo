#include <gtest/gtest.h>
#include <memory>

#include "Client.hpp"
#include "CommunicationServiceMock.hpp"

class ClientShould : public ::testing::Test
{
protected:
	ClientShould() :
		communicationServMock_(std::make_shared<CommunicationServiceMock>()),
		client_(communicationServMock_) {}

	void SetUp()
	{
		argc_ = 1;
		argv_ = new char*[argc_];
		argv_[0] = new char[10];
		argv_[0] = "client";
	}

	void TearDown()
	{
		delete argv_[0];
		delete argv_;
	}

	Client client_;
	CommunicationServiceMockPtr communicationServMock_;
	int argc_;
	char** argv_;
};

TEST_F(ClientShould, PrepareApplicationComponents)
{
	EXPECT_CALL(*communicationServMock_, startService());
	EXPECT_EQ(0, client_.start(argc_, argv_));
}
