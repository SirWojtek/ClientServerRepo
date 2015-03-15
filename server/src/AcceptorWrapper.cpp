#include "AcceptorWrapper.hpp"
#include <stdexcept>
#include <boost/bind.hpp>

void AcceptorWrapper::createAcceptor()
{
	if(ioService_ != nullptr)
	{
		acceptor_ = std::make_shared<tcp::acceptor>(*ioService_,
        	tcp::endpoint(tcp::v4(), AcceptorWrapper::portNumber));
		ioService_ = nullptr;
	}
	else
	{
		throw std::runtime_error("Attempted to initialize acceptor twice.");
	}
}

std::shared_ptr<ServerSession> AcceptorWrapper::createServerSession()
{
	return std::make_shared<ServerSession>(acceptor_->get_io_service());
}

void AcceptorWrapper::runIoService()
{
	acceptor_->get_io_service().run();
}

void AcceptorWrapper::startAccepting(ServerSession& session,
		IServerInitializer* instance)
{
	acceptor_->async_accept(session.getSocket(),
     boost::bind(&IServerInitializer::handleAccept,
         instance, boost::asio::placeholders::error));
}