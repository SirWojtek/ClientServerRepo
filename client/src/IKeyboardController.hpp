#ifndef IKEYBOARD_CONTROLLER_HPP_
#define IKEYBOARD_CONTROLLER_HPP_

#include <memory>

#include <SFML/Window/Event.hpp>

class IKeyboardController
{
public:
    enum KeyDirection
    {
        None,
        Up,
        Down,
        Right,
        Left,
        Exit
    };

    virtual KeyDirection getKeyboardInput() = 0;
    virtual bool wasExitKeyPressed() = 0;
    virtual void keyCallback(const sf::Event&) = 0;
};
using KeyboardControllerPtr = std::shared_ptr<IKeyboardController>;


#endif  // IKEYBOARD_CONTROLLER_HPP_