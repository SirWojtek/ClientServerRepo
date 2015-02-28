#ifndef WORLD_UPDATER_MOCK_HPP_
#define WORLD_UPDATER_MOCK_HPP_

#include <memory>
#include <gmock/gmock.h>

#include "client/src/IWorldUpdater.hpp"

class WorldUpdaterMock : public IWorldUpdater
{
public:
    MOCK_METHOD1(updateModel, void(bool));
};
using WorldUpdaterMockPtr = std::shared_ptr<WorldUpdaterMock>;

#endif  // WORLD_UPDATER_MOCK_HPP_
