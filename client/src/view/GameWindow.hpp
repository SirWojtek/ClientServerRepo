#ifndef GAME_WINDOW_HPP_
#define GAME_WINDOW_HPP_

#include <thread>
#include <memory>
#include <atomic>

#include "IGameWindow.hpp"
#include "IModelPainter.hpp"

#include "common/utilities/Console.hpp"

namespace sf
{
class RenderWindow;
}

namespace view
{

class GameWindow : public IGameWindow
{
public:
    GameWindow(ModelPainterPtr modelPainter);

    virtual void startWindowThread();
    virtual void tearDown();

private:
    void windowMain();
    void pumpEvents(sf::RenderWindow& window);
    void display(sf::RenderWindow& window);

    ModelPainterPtr modelPainter_;

    std::unique_ptr<std::thread> windowThread_;
    std::atomic<bool> exit_;
    Console console_;
};

}

#endif  // GAME_WINDOW_HPP_
