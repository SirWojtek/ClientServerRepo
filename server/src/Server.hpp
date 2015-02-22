#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include "common/utilities/TcpSocket.hpp"
#include "common/utilities/Console.hpp"


class Server
{
public:
    Server() : 
        sessionCount_(0),
        console_("Server")
    {
        tcpSocket_ = std::make_shared<TcpSocket>();
    }

    void run();

private:

    void initServer();
    bool waitForConnection();

    const static unsigned defaultPortNumber_ = TcpSocket::portNumber;
    unsigned sessionCount_;
    std::shared_ptr<TcpSocket> tcpSocket_;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
    std::shared_ptr<std::string> message_;
    Console console_;
};

#endif
