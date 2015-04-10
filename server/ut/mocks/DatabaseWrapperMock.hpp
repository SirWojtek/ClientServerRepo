#ifndef DATABASE_WRAPPER_MOCK_HPP_
#define DATABASE_WRAPPER_MOCK_HPP_

#include <gmock/gmock.h>
#include "server/src/modules/database/IDatabaseWrapper.hpp"

class DatabaseWrapperMock : public IDatabaseWrapper
{
public:
	MOCK_METHOD0(getUsers, Users());
	MOCK_METHOD2(getUsersBy, Users(UserTypes type, unsigned& id));
	MOCK_METHOD2(getUsersBy, Users(UserTypes type, std::string& login));
	MOCK_METHOD2(getUsersBy, Users(UserTypes type, std::vector<int> position));
	MOCK_METHOD2(getUsersBy, Users(UserTypes type, bool isOnline));
};

#endif