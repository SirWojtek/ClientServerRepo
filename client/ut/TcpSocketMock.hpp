#pragma once

#include <gmock/gmock.h>
#include <memory>

#include "ITcpSocket.hpp"

class TcpSocketMock : public ITcpSocket
{
	MOCK_METHOD2(connect, void(const std::string&, const std::string&));
	MOCK_METHOD1(write, void(std::string&));
	MOCK_METHOD1(write, void(const char*));
	MOCK_METHOD0(read, std::shared_ptr<const std::string>());
};