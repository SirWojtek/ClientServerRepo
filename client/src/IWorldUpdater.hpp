#ifndef IWORLD_UPDATER_HPP_
#define IWORLD_UPDATER_HPP_

#include <memory>

class IWorldUpdater
{
public:
	virtual void init() = 0;
    virtual void updateModel(bool isPlayerMoving) = 0;
};
using WorldUpdaterPtr = std::shared_ptr<IWorldUpdater>;

#endif  // IWORLD_UPDATER_HPP_
