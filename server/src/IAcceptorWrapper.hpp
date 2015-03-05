#ifndef I_ACCEPTOR_WRAPPER_HPP_
#define I_ACCEPTOR_WRAPPER_HPP_

#include <boost/asio.hpp>

class IAcceptorWrapper{
public:

	virtual void createAcceptor(boost::asio::io_service& ioService) = 0;
	virtual boost::asio::ip::tcp::acceptor& getInstance() = 0;
};

#endif