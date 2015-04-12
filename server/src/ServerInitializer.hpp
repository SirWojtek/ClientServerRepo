#ifndef SERVER_INITIALIZER_HPP_
#define SERVER_INITIALIZER_HPP_

#define FULL_SERVER_FLAG 5
#undef FULL_SERVER_FLAG

#include <boost/asio/io_service.hpp>
#include <thread>
#include "common/utilities/Console.hpp"
#include "ServerSession.hpp"
#include "IBoostWrapper.hpp"

#ifdef FULL_SERVER_FLAG

#include "modules/database/MysqlDatabaseWrapper.hpp"

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

#else

#include "modules/database/IDatabaseWrapper.hpp"

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
	std::shared_ptr<IDatabaseWrapper> databaseConnector_;
	std::shared_ptr<ServerSession> session_;
	std::vector<std::shared_ptr<std::thread>> sessionThreadArray_;
	std::vector<std::shared_ptr<ServerSession>> sessionArray_;
	Console console_;
};

#endif

#endif