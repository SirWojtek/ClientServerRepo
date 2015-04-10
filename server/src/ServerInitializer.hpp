#ifndef SERVER_INITIALIZER_HPP_
#define SERVER_INITIALIZER_HPP_

#include <boost/asio/io_service.hpp>
#include <thread>
#include "common/utilities/Console.hpp"
#include "ServerSession.hpp"
#include "modules/database/MysqlDatabaseWrapper.hpp"

#include "IBoostWrapper.hpp"

class ServerInitializer : public IServerInitializer
{
public:
	ServerInitializer(std::shared_ptr<IBoostWrapper> wrapper);
	~ServerInitializer();
	void handleAccept(const boost::system::error_code& error);
	void runAsyncAccept();
	void joinThreads();

private:
	std::shared_ptr<IBoostWrapper> wrapper_;
	std::shared_ptr<DatabaseWrapper> databaseConnector_;
	std::shared_ptr<ServerSession> session_;
	std::vector<std::shared_ptr<std::thread>> sessionThreadArray_;
	std::vector<std::shared_ptr<ServerSession>> sessionArray_;
	Console console_;
};

#endif