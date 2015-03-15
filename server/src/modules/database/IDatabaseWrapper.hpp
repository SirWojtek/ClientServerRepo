#ifndef I_DATABASE_WRAPPER_HPP_
#define I_DATABASE_WRAPPER_HPP_

#include <string>
#include <vector>
#include <memory>

enum UserTypes{
	ID,
	LOGIN,
	LASTVISIT,
	XPOS,
	YPOS,
	ZPOS
};

struct User{
	unsigned id;
	std::string login;
	std::string lastVisit;
	std::vector<int> position; // This vector should always have 3 elements (x, y, z)
};

using Users = std::vector<std::shared_ptr<User> >;

class IDatabaseWrapper{
public:
	virtual void getInstance() = 0;
	virtual Users getUsersBy(UserTypes type, unsigned& id) = 0; // getUsersById
	virtual Users getUsersBy(UserTypes type, std::string& login) = 0; // getUsersByLogin
	virtual Users getUsersBy(UserTypes type, std::vector<int> position) = 0; // getUsersByOneOfPositions - only 1 of 3 elements should have value, other 2 should be zeros

};

#endif