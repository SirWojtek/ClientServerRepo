#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>

class ITcpSocket
{
public:
	virtual ~ITcpSocket() {}
	virtual void connect(const std::string& host, const std::string& port) = 0;
	virtual void write(std::string& message) = 0;
	virtual void write(const char* message) = 0;
	virtual std::shared_ptr<const std::string> read() = 0;
};
typedef std::shared_ptr<ITcpSocket> TcpSocketPtr;
