#include "MysqlDatabaseWrapper.hpp"
#include <iostream>
#include <istream>
#include <ostream>

Users DatabaseWrapper::getUsers()
{
	Users foundUsers;
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT id, login, lastVisit, xPosition, yPosition, zPosition, isOnline from users");
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	return foundUsers;
}

Users DatabaseWrapper::getUsersBy(UserTypes type, unsigned& id)
{
	Users foundUsers;
	return foundUsers;
}

Users DatabaseWrapper::getUsersBy(UserTypes type, std::string& login)
{
	Users foundUsers;
	return foundUsers;
}

Users DatabaseWrapper::getUsersBy(UserTypes type, std::vector<int> position)
{
	Users foundUsers;
	return foundUsers;
}

Users DatabaseWrapper::getUsersBy(UserTypes type, bool isOnline)
{
	Users foundUsers;
	return foundUsers;
}
