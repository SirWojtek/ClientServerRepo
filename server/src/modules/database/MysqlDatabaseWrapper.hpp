#ifndef MYSQL_DATABASE_WRAPPER_HPP_
#define MYSQL_DATABASE_WRAPPER_HPP_

#include "IDatabaseWrapper.hpp"
#include "common/external/soci/src/core/soci.h"
#include "common/external/soci/src/backends/mysql/soci-mysql.h"

class DatabaseWrapper : public IDatabaseWrapper
{
public:
	void getInstance();
	Users getUsersBy(UserTypes type, unsigned& id);
	Users getUsersBy(UserTypes type, std::string& login);
	Users getUsersBy(UserTypes type, std::vector<int> position);
private:
	std::shared_ptr<soci::session> databaseConnector;
};

#endif 