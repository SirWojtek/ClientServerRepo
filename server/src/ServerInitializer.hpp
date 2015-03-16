#ifndef SERVER_INITIALIZER_HPP_
#define SERVER_INITIALIZER_HPP_

#include <boost/asio/io_service.hpp>
#include <thread>
#include "common/utilities/Console.hpp"
#include "ServerSession.hpp"

#include "IBoostWrapper.hpp"

class ServerInitializer : public IServerInitializer
{
public:
	ServerInitializer(std::shared_ptr<IBoostWrapper> wrapper);
	void handleAccept(const boost::system::error_code& error);
	void runAsyncAccept();

private:
	std::shared_ptr<IBoostWrapper> wrapper_;
	std::shared_ptr<ServerSession> session_;
	std::vector<std::shared_ptr<std::thread>> sessionArray_;
	Console console_;
};

#endif