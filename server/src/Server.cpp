#include <boost/asio.hpp>
#include <stdexcept>

#include "common/utilities/TcpSocket.hpp"
#include "Server.hpp"

using boost::asio::ip::tcp;

void Server::run()
{
    initServer();
    console_.info << "Server started.";

    while (waitForConnection())
    {
        sessionCount_++;
        console_.info << "Waiting for connection...";
    }
}

void Server::initServer()
{
    acceptor_ = tcpSocket_->establishServer();
}

bool Server::waitForConnection()
{
    try
    {
        acceptor_->accept(*tcpSocket_->getSocket());
        return true;
    }
    catch(const std::runtime_error& e)
    {
        throw std::runtime_error(e.what());
    }
}
