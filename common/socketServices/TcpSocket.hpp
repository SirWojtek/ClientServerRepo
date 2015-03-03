#ifndef TCP_SOCKET_HPP_
#define TCP_SOCKET_HPP_

#include "common/utilities/Console.hpp"
#include "ITcpSocket.hpp"

#include <string>
#include <memory>
#include <boost/asio.hpp>

class TcpSocket : public ITcpSocket
{
public:
    TcpSocket();

    void connect(const std::string& host, const std::string& port);
    void write(std::string& message);
    void write(const char* message);
    std::shared_ptr<const std::string> read();
    std::shared_ptr<boost::asio::ip::tcp::socket> getSocket();
    void cancellAllAsyncServices();

private:
    bool readWithTimeout(boost::asio::streambuf& buffer);
    void runIoService(const bool& readed, const bool& timeout, boost::asio::deadline_timer& timer);
    std::shared_ptr<std::string> getMessageFromBuffer(boost::asio::streambuf& buffer);

    std::unique_ptr<boost::asio::io_service> ioService_;
    std::unique_ptr<boost::asio::ip::tcp::socket> tcpSocket_;

    Console console_;
};

#endif  // TCP_SOCKET_HPP_
