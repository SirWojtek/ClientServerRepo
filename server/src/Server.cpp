#include <boost/asio.hpp>
#include <stdexcept>

#include "common/utilities/TcpSocket.hpp"
#include "Server.hpp"

using boost::asio::ip::tcp;

void Server::run()
{
    initServer();
    console_.info << "Server started.";

    waitForConnection();
    tcpSocket_->read();
}

void Server::initServer()
{
    acceptor_ = tcpSocket_->establishServer();
}

void Server::waitForConnection()
{
    try
    {
        console_.info << "Waiting for connection...";
        tcpSocket_->acceptConnection(acceptor_);
    }
    catch(const std::runtime_error& e)
    {
        throw std::runtime_error(e.what());
    }
}
