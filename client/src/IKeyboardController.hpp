#ifndef IKEYBOARD_CONTROLLER_HPP_
#define IKEYBOARD_CONTROLLER_HPP_

#include <memory>

class IKeyboardController
{
public:
    enum KeyDirection
    {
        Up,
        Down,
        Right,
        Left
    };

    virtual KeyDirection getKeyboardInput() = 0;
    virtual bool wasExitKeyPressed() = 0;
};
using KeyboardControllerPtr = std::shared_ptr<IKeyboardController>;


#endif  // IKEYBOARD_CONTROLLER_HPP_