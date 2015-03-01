#ifndef SERVER_INITIALIZER_HPP_
#define SERVER_INITIALIZER_HPP_

#include <boost/asio.hpp>
#include <thread>
#include "ServerSession.hpp"
#include "common/utilities/Console.hpp"

using boost::asio::ip::tcp;

class ServerInitializer
{
public:
	ServerInitializer(boost::asio::io_service& ioService);
	void handleAccept(const boost::system::error_code& error);

private:
	std::shared_ptr<tcp::acceptor> acceptor_;
	std::shared_ptr<ServerSession> session_;
	std::vector<std::shared_ptr<std::thread>> sessionArray_;
	Console console_;
	const static unsigned portNumber = 4001;
};

#endif