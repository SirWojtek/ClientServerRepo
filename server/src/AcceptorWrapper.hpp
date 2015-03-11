#ifndef ACCEPTOR_WRAPPER_HPP_
#define ACCEPTOR_WRAPPER_HPP_

#include <stdexcept>
#include "IAcceptorWrapper.hpp"
#include <boost/asio.hpp>


class AcceptorWrapper : public IAcceptorWrapper
{
public:
	AcceptorWrapper(std::shared_ptr<boost::asio::io_service> ioService) :
	ioService_(ioService)
	{ }

	void createAcceptor()
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

	std::shared_ptr<ServerSession> createServerSession()
	{
		return std::make_shared<ServerSession>(acceptor_->get_io_service());
	}

	void runIoService()
	{
		acceptor_->get_io_service().run();
	}

	void startAccepting(ServerSession& session,
		IServerInitializer* instance)
	{
		acceptor_->async_accept(session.getSocket(),
         boost::bind(&IServerInitializer::handleAccept,
             instance, boost::asio::placeholders::error));
	}

private:
	std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
	std::shared_ptr<boost::asio::io_service> ioService_;
	const static unsigned portNumber = 4001;
};

#endif