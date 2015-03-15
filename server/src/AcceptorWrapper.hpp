#ifndef ACCEPTOR_WRAPPER_HPP_
#define ACCEPTOR_WRAPPER_HPP_

#include "IAcceptorWrapper.hpp"
#include <boost/asio.hpp>


class AcceptorWrapper : public IAcceptorWrapper
{
public:
	AcceptorWrapper(std::shared_ptr<boost::asio::io_service> ioService) :
	ioService_(ioService)
	{ }

	void createAcceptor();
	std::shared_ptr<ServerSession> createServerSession();
	void runIoService();
	void startAccepting(ServerSession& session, IServerInitializer* instance);

private:
	std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
	std::shared_ptr<boost::asio::io_service> ioService_;
	const static unsigned portNumber = 4001;
};

#endif