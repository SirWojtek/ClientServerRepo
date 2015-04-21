#include "MysqlDatabaseWrapper.hpp"
#include <iostream>
#include <istream>
#include <ostream>

#include "boost/tuple/tuple_comparison.hpp"

Users DatabaseWrapper::getUsers()
{
	Users foundUsers;
	connectorMutex.lock();
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT * from users");
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	connectorMutex.unlock();
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
	connectorMutex.lock();
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT * from users where id = :id", soci::use(id));
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	connectorMutex.unlock();
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
	connectorMutex.lock();
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT * from users where login = :login", soci::use(login));
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	connectorMutex.unlock();
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
	connectorMutex.lock();
	soci::rowset<User> rows = (databaseConnector_->prepare <<
		"SELECT * from users where isOnline = :isOnline", soci::use(isOnlineIntValue));
	std::copy(rows.begin(), rows.end(), std::back_inserter(foundUsers));
	connectorMutex.unlock();
	return foundUsers;
}

bool DatabaseWrapper::updateUser(User userToUpdate)
{
	connectorMutex.lock();
	*databaseConnector_ << "UPDATE users SET login = :login, lastVisit = :lastVisit, xPosition = :xPos, yPosition = :yPos, zPosition = :zPos, isOnline = :isOn WHERE id = :id",
		soci::use(userToUpdate.get<1>()), soci::use(userToUpdate.get<2>()),
		soci::use(userToUpdate.get<3>()), soci::use(userToUpdate.get<4>()),
		soci::use(userToUpdate.get<5>()), soci::use(userToUpdate.get<6>()),
		soci::use(userToUpdate.get<0>());
	connectorMutex.unlock();
	return true;
	// TODO - try to remember why I thought it would be useful
	// if (userIsEqualToPattern(userToUpdate.get<0>(), userToUpdate))
	// {
	// 	return true;
	// }
	// else
	// {
	// 	console_.error << "Failed to update player!";
	// 	return false;
	// }
}

Users DatabaseWrapper::getUsersBy(UserTypes type, std::vector<int> position)
{
	Users foundUsers;
	if (type != UserTypes::POS)
	{
		console_.error << "Trying to get users by POS, but specified other type: " << type;
		return foundUsers;

	}
	connectorMutex.lock();
	soci::rowset<User> rows = (databaseConnector_->prepare << "SELECT * from users");
	MarkedPositions positions = checkMarkedPositions(position);
	connectorMutex.unlock();
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

bool DatabaseWrapper::userIsEqualToPattern(unsigned idToCheck, User userToCheck)
{
	auto UsersFromDb = getUsersBy(UserTypes::ID, idToCheck);
	if (UsersFromDb.size() != 1)
	{
		return false;
	}
	if (areUsersEqual(UsersFromDb[0], userToCheck))
	{
		return true;
	}
	return false;
}

bool DatabaseWrapper::areUsersEqual(User alice, User bob) // excludes std::tm part
{
	if (alice.get<0>() == bob.get<0>())
	{
		if (alice.get<1>() == bob.get<1>())
		{
			if (alice.get<3>() == bob.get<3>())
			{
				if (alice.get<4>() == bob.get<4>())
				{
					if (alice.get<5>() == bob.get<5>())
					{
						if (alice.get<6>() == bob.get<6>())
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}