#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <stdexcept>

#include "ServerInitializer.hpp"

using boost::asio::ip::tcp;

ServerInitializer::ServerInitializer(
    std::shared_ptr<IAcceptorWrapper> acceptor) :
    acceptor_(acceptor),
    session_(acceptor_->createServerSession()),
    console_("ServerInitializer")
{ }

void ServerInitializer::runAsyncAccept()
{
    // acceptor_->getInstance().async_accept(session_->getSocket(),
    //      boost::bind(&ServerInitializer::handleAccept,
    //          this, boost::asio::placeholders::error));
    acceptor_->startAccepting(*session_, this);
    acceptor_->runIoService();
}

void ServerInitializer::handleAccept(const boost::system::error_code& error)
{
    if (!error)
    {
        sessionArray_.push_back(session_->start());
        session_ = acceptor_->createServerSession();
        // acceptor_->getInstance().async_accept(session_->getSocket(),
        //      boost::bind(&ServerInitializer::handleAccept,
        //          this, boost::asio::placeholders::error));
        acceptor_->startAccepting(*session_, this);
    }
}