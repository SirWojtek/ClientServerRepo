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
	ASSERT_NE(userData.size(), 0);
}