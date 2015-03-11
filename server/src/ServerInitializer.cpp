#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <stdexcept>

#include "ServerInitializer.hpp"

using boost::asio::ip::tcp;

ServerInitializer::ServerInitializer(
    std::shared_ptr<AcceptorWrapper> acceptor) :
    acceptor_(acceptor),
    session_(acceptor_->createServerSession()),
    console_("ServerInitializer")
{ }

void ServerInitializer::runAsyncAccept()
{
    acceptor_->startAccepting(*session_, this);
}

void ServerInitializer::handleAccept(const boost::system::error_code& error)
{
    if (!error)
    {
        sessionArray_.push_back(session_->start());
        session_ = acceptor_->createServerSession();
        acceptor_->startAccepting(*session_, this);
    }
}