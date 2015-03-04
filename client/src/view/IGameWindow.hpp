#ifndef IGAME_WINDOW_HPP_
#define IGAME_WINDOW_HPP_

#include <memory>

namespace view
{

class IGameWindow
{
public:
    virtual void startWindowThread() = 0;
    virtual void tearDown() = 0;
};
using GameWindowPtr = std::shared_ptr<IGameWindow>;

}

#endif  // IGAME_WINDOW_HPP_
