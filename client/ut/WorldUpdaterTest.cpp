#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <stdexcept>

#include "client/src/WorldUpdater.hpp"
// #include "common/messages/UpdatePlayer.hpp"
#include "common/messages/MessageTypes.hpp"

#include "ObjectsFacadeMock.hpp"
#include "CommunicationServiceMock.hpp"

#include "client/src/model/objects/Object.hpp"

using namespace ::testing;
// using namespace common;

class WorldUpdaterShould : public ::testing::Test
{
protected:
    WorldUpdaterShould() :
        objectsFacadeMock_(std::make_shared<ObjectsFacadeMock>()),
        communicationServMock_(std::make_shared<CommunicationServiceMock>()),
        playerObject_(std::make_shared<model::Object>()),
        worldUpdater_(std::make_shared<WorldUpdater>(
            objectsFacadeMock_, communicationServMock_)) {}

    void SetUp()
    {
        EXPECT_CALL(*communicationServMock_, startService());
        EXPECT_CALL(*objectsFacadeMock_, getPlayerObject())
            .WillOnce(Return(playerObject_));
        EXPECT_CALL(*objectsFacadeMock_, loadMaps());

        worldUpdater_->init();
    }

    void TearDown()
    {
        EXPECT_CALL(*communicationServMock_, tearDown());
    }

    ObjectsFacadeMockPtr objectsFacadeMock_;
    CommunicationServiceMockPtr communicationServMock_;
    model::ObjectPtr playerObject_;

    WorldUpdaterPtr worldUpdater_;
};

TEST_F(WorldUpdaterShould, throwIfUpdateEnvironmentMessageConversionFails)
{
    std::shared_ptr<std::string> message = std::make_shared<std::string>();

    EXPECT_CALL(*communicationServMock_,
        getMessage(common::messagetype::UpdateEnvironment, false))
    .WillOnce(Return(message));

    EXPECT_THROW(worldUpdater_->updateModel(false), std::runtime_error);
}


