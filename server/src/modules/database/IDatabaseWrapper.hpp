#ifndef I_DATABASE_WRAPPER_HPP_
#define I_DATABASE_WRAPPER_HPP_

#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <boost/tuple/tuple.hpp>

enum UserTypes{
	ID = 0,
	LOGIN = 1,
	LASTVISIT = 2,
	POS = 3,
	ISONLINE = 4
};

enum MarkedPositions{
	// X = 1 ; Y = 2 ; Z = 4 => XY = X+Y = 3 etc.
	None = 0,
	X = 1,
	Y = 2,
	XY = 3,
	Z = 4,
	XZ = 5,
	YZ = 6,
	XYZ = 7
};

// User - id, login, lastVisit, xPos, yPos, zPos, isOnline
using User = boost::tuple<unsigned, std::string, std::tm, int, int, int, int>;
using Users = std::vector<User>;

class IDatabaseWrapper{
public:
	virtual Users getUsers() = 0;
	virtual Users getUsersBy(UserTypes type, unsigned& id) = 0; // getUsersById
	virtual Users getUsersBy(UserTypes type, std::string& login) = 0; // getUsersByLogin
	virtual Users getUsersBy(UserTypes type, std::vector<int> position) = 0; // getUsersByOneOfPositions
	virtual Users getUsersBy(UserTypes type, bool isOnline) = 0; // getUsersByOnlineStatus

};

#endif