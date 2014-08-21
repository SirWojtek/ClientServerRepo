#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>

#include "ITcpSocket.hpp"
#include "Console.hpp"

class TcpSocket : public ITcpSocket
{
public:
    TcpSocket();

    void connect(const std::string& host, const std::string& port);
    void write(std::string& message);
    void write(const char* message);
    std::shared_ptr<const std::string> read();

private:
    std::unique_ptr<boost::asio::io_service> ioService_;
    std::unique_ptr<boost::asio::ip::tcp::socket> tcpSocket_;

    Console console_;

    const static size_t maxMessageSize = 8192;
};
