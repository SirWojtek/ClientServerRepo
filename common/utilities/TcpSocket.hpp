#ifndef TCP_SOCKET_HPP_
#define TCP_SOCKET_HPP_

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
    std::shared_ptr<boost::asio::ip::tcp::acceptor> establishServer();
    void acceptConnection(std::shared_ptr<boost::asio::ip::tcp::acceptor> serverAcceptor);

    const static unsigned portNumber = 4001;

private:
    bool readWithTimeout(boost::asio::streambuf& buffer);
    void runIoService(const bool& readed, const bool& timeout, boost::asio::deadline_timer& timer);
    std::shared_ptr<std::string> getMessageFromBuffer(boost::asio::streambuf& buffer);

    std::unique_ptr<boost::asio::io_service> ioService_;
    std::unique_ptr<boost::asio::ip::tcp::socket> tcpSocket_;

    Console console_;

    const static size_t maxMessageSize = 8192;
    const static unsigned readTimeout = 2;
    const static char readDelim = ';';
};

#endif  // TCP_SOCKET_HPP_
