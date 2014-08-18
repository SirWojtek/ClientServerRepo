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
    boost::asio::connect(*tcpSocket_, resolver.resolve({host, port}));

    if (!isHostFound())
        throw std::runtime_error("Can not connect to host");
}

bool TcpSocket::isHostFound()
{
    return !boost::asio::error::host_not_found;
}

void TcpSocket::write(const char* message)
{
    std::string stringMessage(message);
    write(stringMessage);
}

void TcpSocket::write(std::string& message)
{
    boost::asio::write(
        *tcpSocket_, boost::asio::buffer(message.c_str(), message.size()));
}

std::shared_ptr<const std::string> TcpSocket::read()
{
    std::shared_ptr<std::string> message(std::make_shared<std::string>());
    message->reserve(maxMessageSize);

    size_t replyLength = boost::asio::read(
        *tcpSocket_, boost::asio::buffer(&(*message)[0], maxMessageSize));

    if (replyLength == maxMessageSize)
        throw std::runtime_error("Message readed from host is too large");

    return message;
}
