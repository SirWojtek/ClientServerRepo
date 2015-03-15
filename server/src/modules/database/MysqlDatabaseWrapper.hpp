#ifndef MYSQL_DATABASE_WRAPPER_HPP_
#define MYSQL_DATABASE_WRAPPER_HPP_

#include <stdexcept>

#include "IDatabaseWrapper.hpp"

#define SOCI_USE_BOOST

#include "common/external/soci/src/core/soci.h"
#include "common/external/soci/src/backends/mysql/soci-mysql.h"
#include "common/utilities/Console.hpp"
#include <boost/tuple/tuple.hpp>

class DatabaseWrapper : public IDatabaseWrapper
{
public:
	DatabaseWrapper() :
		console_("DatabaseWrapper")
	{
		try
		{
			databaseConnector_ = std::make_shared<soci::session>(soci::mysql,
				"db=game_db user=root password='root'");
		}
		catch(const std::runtime_error& e)
		{
		  throw std::runtime_error(e.what());
		}
	}

	Users getUsers();
	Users getUsersBy(UserTypes type, unsigned& id);
	Users getUsersBy(UserTypes type, std::string& login);
	Users getUsersBy(UserTypes type, std::vector<int> position);
	Users getUsersBy(UserTypes type, bool isOnline);
private:
	std::shared_ptr<soci::session> databaseConnector_;
	Console console_;
};

#endif 