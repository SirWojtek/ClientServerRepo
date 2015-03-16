#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <stdexcept>

#include "ServerInitializer.hpp"

ServerInitializer::ServerInitializer(
    std::shared_ptr<IBoostWrapper> wrapper) :
    wrapper_(wrapper),
    session_(std::make_shared<ServerSession>(wrapper_, wrapper_->getLatestSocketNumber())),
    console_("ServerInitializer")
{ }

void ServerInitializer::runAsyncAccept()
{
    wrapper_->startAccepting(*session_, this, wrapper_->getLatestSocketNumber());
}

void ServerInitializer::handleAccept(const boost::system::error_code& error)
{
    if (!error)
    {
        sessionArray_.push_back(session_->start());
        wrapper_->addSocket();
        session_ = std::make_shared<ServerSession>(wrapper_, wrapper_->getLatestSocketNumber());
        wrapper_->startAccepting(*session_, this,  wrapper_->getLatestSocketNumber());
    }
}