#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <stdexcept>

#include "ServerInitializer.hpp"
#include "SocketServicesWrapper.hpp"
#include "common/socketServices/MessageQueue.hpp"

#ifdef FULL_SERVER_FLAG

ServerInitializer::ServerInitializer(
    std::shared_ptr<IBoostWrapper> wrapper) :
    wrapper_(wrapper),
    databaseConnector_(std::make_shared<DatabaseWrapper>(std::string("game_db"))),
    console_("ServerInitializer")
{ }

#else

ServerInitializer::ServerInitializer(
    std::shared_ptr<IBoostWrapper> wrapper) :
    wrapper_(wrapper),
    console_("ServerInitializer")
{ }

#endif

ServerInitializer::~ServerInitializer()
{ }

void ServerInitializer::runAsyncAccept()
{
    if (databaseConnector_)
    {
        console_.info << "Database is alive";
    }
    else
    {
        console_.info << "Database is not alive";
    }
    session_ = std::make_shared<ServerSession>(wrapper_,
        std::make_shared<SocketServicesWrapper>(std::make_shared<MessageQueue>()),
        std::make_shared<SocketServicesWrapper>(std::make_shared<MessageQueue>()),
        wrapper_->getLatestSocketNumber(), databaseConnector_);
    wrapper_->startAccepting(*session_, this, wrapper_->getLatestSocketNumber());
}

void ServerInitializer::handleAccept(const boost::system::error_code& error)
{
    if (!error)
    {
        sessionThreadArray_.push_back(session_->start());
        sessionArray_.push_back(session_);
        wrapper_->addSocket();
        session_ = std::make_shared<ServerSession>(wrapper_,
            std::make_shared<SocketServicesWrapper>(std::make_shared<MessageQueue>()),
            std::make_shared<SocketServicesWrapper>(std::make_shared<MessageQueue>()),
            wrapper_->getLatestSocketNumber(), databaseConnector_);
        wrapper_->startAccepting(*session_, this,  wrapper_->getLatestSocketNumber());
    }
}

void ServerInitializer::joinThreads()
{
    for (unsigned i=0; i < sessionArray_.size(); i++)
    {
        sessionArray_[i]->stop();
        sessionThreadArray_[i]->join();
    }
}