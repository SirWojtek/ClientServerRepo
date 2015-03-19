#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

#include "server/src/modules/database/MysqlDatabaseWrapper.hpp"

using namespace ::testing;

class MysqlDatabaseWrapperShould : public ::testing::Test
{
protected:
    MysqlDatabaseWrapperShould() :
    wrapper_(std::make_shared<DatabaseWrapper>())
    {}

    std::shared_ptr<DatabaseWrapper> wrapper_;
};

TEST_F(MysqlDatabaseWrapperShould, getUsersFromDatabase)
{
	Users userData = wrapper_->getUsers();
	ASSERT_EQ(userData.size(), 3);
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedId)
{
	unsigned id = 1;
	Users userData = wrapper_->getUsersBy(UserTypes::ID, id);
	ASSERT_EQ(userData.size(), 1);
	ASSERT_EQ(userData[0].get<1>(), "Gettor");
}

TEST_F(MysqlDatabaseWrapperShould, giveNothingWhenGetUsersByIdGetsWrongType)
{
	unsigned id = 1;
	Users userData = wrapper_->getUsersBy(UserTypes::LOGIN, id);
	ASSERT_EQ(userData.size(), 0);
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedLogin)
{
	std::string login = "Gettor";
	Users userData = wrapper_->getUsersBy(UserTypes::LOGIN, login);
	ASSERT_EQ(userData.size(), 1);
	ASSERT_EQ(userData[0].get<0>(), 1);
}

TEST_F(MysqlDatabaseWrapperShould, giveNothingWhenGetUsersByLoginGetsWrongType)
{
	std::string login = "Gettor";
	Users userData = wrapper_->getUsersBy(UserTypes::ID, login);
	ASSERT_EQ(userData.size(), 0);
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedXPos)
{
	std::vector<int> pos {10, -1, -1};
	Users userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 1);
	ASSERT_EQ(userData[0].get<1>(), "SirWojtek");
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedYPos)
{
	std::vector<int> pos {-1, 10, -1};
	Users userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 1);
	ASSERT_EQ(userData[0].get<1>(), "SirWojtek");
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedZPos)
{
	std::vector<int> pos {-1, -1, 0};
	Users userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 3);
	ASSERT_EQ(userData[0].get<1>(), "Gettor");
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedXYPos)
{
	std::vector<int> pos {30, 15, -1};
	Users userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 1);
	ASSERT_EQ(userData[0].get<1>(), "RandomDude");
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedXZPos)
{
	std::vector<int> pos {30, -1, 0};
	Users userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 1);
	ASSERT_EQ(userData[0].get<1>(), "RandomDude");
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedXYZPos)
{
	std::vector<int> pos {30, 15, 0};
	Users userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 1);
	ASSERT_EQ(userData[0].get<1>(), "RandomDude");
}

TEST_F(MysqlDatabaseWrapperShould, getNoUsersWhenSpecifiedNullPositions)
{
	std::vector<int> pos {-1, -1, -1};
	Users userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 0);
}

TEST_F(MysqlDatabaseWrapperShould, getNoUsersWhenSpecifiedPositionsDontHaveAny)
{
	std::vector<int> pos {21, 13, 8};
	Users userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 0);

	pos = {20, 20, 5};
	userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 0);

	pos = {20, 10, 5};
	userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 0);

	pos = {20, 10, 0};
	userData = wrapper_->getUsersBy(UserTypes::POS, pos);
	ASSERT_EQ(userData.size(), 0);
}

TEST_F(MysqlDatabaseWrapperShould, giveNothingWhenGetUsersByPosGetsWrongType)
{
	std::vector<int> pos {30, 15, 0};
	Users userData = wrapper_->getUsersBy(UserTypes::ID, pos);
	ASSERT_EQ(userData.size(), 0);
}

TEST_F(MysqlDatabaseWrapperShould, getUsersBySpecifiedOnlineStatus)
{
	bool isOnline = false;
	Users userData = wrapper_->getUsersBy(UserTypes::ISONLINE, isOnline);
	ASSERT_EQ(userData.size(), 3);
	ASSERT_EQ(userData[0].get<1>(), "Gettor");
}

TEST_F(MysqlDatabaseWrapperShould, giveNothingWhenGetUsersByOnlineStatusGetsWrongType)
{
	bool isOnline = false;
	Users userData = wrapper_->getUsersBy(UserTypes::ID, isOnline);
	ASSERT_EQ(userData.size(), 0);
}