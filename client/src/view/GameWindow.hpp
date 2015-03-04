#ifndef GAME_WINDOW_HPP_
#define GAME_WINDOW_HPP_

#include <thread>
#include <memory>
#include <atomic>

#include "IGameWindow.hpp"

#include "common/utilities/Console.hpp"

namespace view
{

class GameWindow : public IGameWindow
{
public:
    GameWindow();

    virtual void startWindowThread();
    virtual void tearDown();

private:
    void windowMain();

    std::unique_ptr<std::thread> windowThread_;
    std::atomic<bool> exit_;
    Console console_;
};

}

#endif  // GAME_WINDOW_HPP_
