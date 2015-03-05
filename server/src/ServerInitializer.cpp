#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <stdexcept>

#include "ServerInitializer.hpp"

using boost::asio::ip::tcp;

ServerInitializer::ServerInitializer(IoServiceWrapper& ioService) :
    console_("ServerInitializer")
{
    acceptor_.createAcceptor(ioService.getInstance());
    session_ = std::make_shared<ServerSession>(acceptor_.getInstance().get_io_service());
}

void ServerInitializer::runAsyncAccept()
{
    acceptor_.getInstance().async_accept(session_->getSocket(),
        boost::bind(&ServerInitializer::handleAccept, this, boost::asio::placeholders::error));
    acceptor_.getInstance().get_io_service().run();
}

void ServerInitializer::handleAccept(const boost::system::error_code& error)
{
    if (!error)
    {
        sessionArray_.push_back(session_->start());
        session_ = std::make_shared<ServerSession>(acceptor_.getInstance().get_io_service());
        acceptor_.getInstance().async_accept(session_->getSocket(),
            boost::bind(&ServerInitializer::handleAccept, this, boost::asio::placeholders::error));
    }
}