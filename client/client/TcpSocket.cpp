#include <string>
#include <exception>
#include <memory>
#include <boost/asio.hpp>

#include "TcpSocket.hpp"

TcpSocket::TcpSocket() :
    ioService_(new boost::asio::io_service()),
    tcpSocket_(new boost::asio::ip::tcp::socket(*ioService_)) {}

void TcpSocket::connect(const std::string& host, const std::string& port)
{
	boost::asio::ip::tcp::resolver resolver(*ioService_);

	try
	{
		boost::asio::connect(*tcpSocket_, resolver.resolve({ host, port }));
	}
	catch (boost::system::system_error& e)
	{
		throw std::runtime_error(e.what());
	}
}

void TcpSocket::write(const char* message)
{
    std::string stringMessage(message);
    write(stringMessage);
}

void TcpSocket::write(std::string& message)
{
	try
	{
		boost::asio::write(
			*tcpSocket_, boost::asio::buffer(message.c_str(), message.size()));
	}
	catch (boost::system::system_error& e)
	{
		throw std::runtime_error(e.what());
	}
}

std::shared_ptr<const std::string> TcpSocket::read()
{
	size_t replyLength;
    std::shared_ptr<std::string> message(std::make_shared<std::string>());
    message->reserve(maxMessageSize);

	try
	{
		replyLength = boost::asio::read(
			*tcpSocket_, boost::asio::buffer(&(*message)[0], maxMessageSize));
	}
	catch (boost::system::system_error& e)
	{
		throw std::runtime_error(e.what());
	}

    if (replyLength == maxMessageSize)
        throw std::runtime_error("Message readed from host is too large");

    return message;
}
