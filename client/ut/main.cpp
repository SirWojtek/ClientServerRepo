#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

#include "ITcpSocket.hpp"

class TcpSocketMock : public ITcpSocket
{
	MOCK_METHOD2(connect, void(const std::string&, const std::string&));
};

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	std::cout << std::endl;
	system("pause");
	return 0;
}