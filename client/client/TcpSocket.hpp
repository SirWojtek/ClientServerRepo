#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>


class ITcpSocket
{
public:
    virtual void connect(const std::string& host, const std::string& port) = 0;
    virtual void write(std::string& message) = 0;
    virtual void write(const char* message) = 0;
    virtual std::shared_ptr<const std::string> read() = 0;
};

class TcpSocket : public ITcpSocket
{
public:
    TcpSocket();

    void connect(const std::string& host, const std::string& port);
    void write(std::string& message);
    void write(const char* message);
    std::shared_ptr<const std::string> read();

private:
    void throwIfThereIsError(boost::asio::ip::tcp::resolver::iterator it);
    bool isHostFound();

    std::unique_ptr<boost::asio::io_service> ioService_;
    std::unique_ptr<boost::asio::ip::tcp::socket> tcpSocket_;

    const static size_t maxMessageSize = 8192;
};
