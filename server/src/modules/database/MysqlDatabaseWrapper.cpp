#include "MysqlDatabaseWrapper.hpp"
#include <iostream>
#include <istream>
#include <ostream>

Users DatabaseWrapper::getUsers()
{
	Users foundUsers;
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT * from users");
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	return foundUsers;
}

Users DatabaseWrapper::getUsersBy(UserTypes type, unsigned& id)
{
	Users foundUsers;
	if (type != UserTypes::ID)
	{
		console_.error << "Trying to get users by ID, but specified other type: " << type;
		return foundUsers;
	}
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT * from users where id = :id", soci::use(id));
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	return foundUsers;
}

Users DatabaseWrapper::getUsersBy(UserTypes type, std::string& login)
{
	Users foundUsers;
	if (type != UserTypes::LOGIN)
	{
		console_.error << "Trying to get users by LOGIN, but specified other type: " << type;
		return foundUsers;
	}
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT * from users where login = :login", soci::use(login));
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	return foundUsers;
}

Users DatabaseWrapper::getUsersBy(UserTypes type, bool isOnline)
{
	Users foundUsers;
	if (type != UserTypes::ISONLINE)
	{
		console_.error << "Trying to get users by ISONLINE, but specified other type: " << type;
		return foundUsers;
	}
	int isOnlineIntValue = ((isOnline) ? 1 : 0 );
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT * from users where isOnline = :isOnline", soci::use(isOnlineIntValue));
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	return foundUsers;
}

Users DatabaseWrapper::getUsersBy(UserTypes type, std::vector<int> position)
{
	Users foundUsers;
	if (type != UserTypes::POS)
	{
		console_.error << "Trying to get users by POS, but specified other type: " << type;
		return foundUsers;

	}
	soci::rowset<User> rows = (databaseConnector_->prepare << "SELECT * from users");
	MarkedPositions positions = checkMarkedPositions(position);
	switch(positions)
	{
		case X:
			rows = (databaseConnector_->prepare <<
				"SELECT * from users where xPosition = :xpos", soci::use(position[0]));
			std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
			break;
		case Y:
			rows = (databaseConnector_->prepare <<
				"SELECT * from users where yPosition = :ypos", soci::use(position[1]));
			std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
			break;
		case Z:
			rows = (databaseConnector_->prepare <<
				"SELECT * from users where zPosition = :zpos", soci::use(position[2]));
			std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
			break;
		case XY:
			rows = (databaseConnector_->prepare <<
				"SELECT * from users where xPosition = :xpos and yPosition = :ypos",
				soci::use(position[0]), soci::use(position[1]));
			std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
			break;
		case XZ:
			rows = (databaseConnector_->prepare <<
				"SELECT * from users where xPosition = :xpos and zPosition = :zpos",
				soci::use(position[0]), soci::use(position[2]));
			std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
			break;
		case YZ:
			rows = (databaseConnector_->prepare <<
				"SELECT * from users where yPosition = :ypos and zPosition = :zpos",
				soci::use(position[1]), soci::use(position[2]));
			std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
			break;
		case XYZ:
			rows = (databaseConnector_->prepare <<
				"SELECT * from users where xPosition = :xpos and yPosition = :ypos and zPosition = :zpos",
				soci::use(position[0]), soci::use(position[1]), soci::use(position[2]));
			std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
			break;
		case None:
			console_.error << "Tried to get users by POS, but couldn't deduce POS";
	}

	return foundUsers;
}

MarkedPositions DatabaseWrapper::checkMarkedPositions(std::vector<int> position)
{
	// check MarkedPositions definition for hints
	int marker = 0;
	if (position[0] != -1) marker += 1;
	if (position[1] != -1) marker += 2;
	if (position[2] != -1) marker += 4;
	return static_cast<MarkedPositions>(marker);
}