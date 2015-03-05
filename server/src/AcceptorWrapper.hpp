#ifndef ACCEPTOR_WRAPPER_HPP_
#define ACCEPTOR_WRAPPER_HPP_

#include <stdexcept>
#include "IAcceptorWrapper.hpp"

class AcceptorWrapper : public IAcceptorWrapper
{
public:
	AcceptorWrapper()
	{ }

	void createAcceptor(boost::asio::io_service& ioService)
	{
		acceptor_ = std::make_shared<tcp::acceptor>(ioService,
        	tcp::endpoint(tcp::v4(), AcceptorWrapper::portNumber));
	}
	
	boost::asio::ip::tcp::acceptor& getInstance()
	{
		if (acceptor_ != nullptr)
		{
			return *acceptor_;
		}
		throw std::invalid_argument("Attepted to get ininitialized Acceptor object.");
	}

private:
	std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
	const static unsigned portNumber = 4001;
};

#endif