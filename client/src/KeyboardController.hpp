#ifndef KEYBOARD_CONTROLLER_HPP_
#define KEYBOARD_CONTROLLER_HPP_

#include "IKeyboardController.hpp"

class KeyboardController : public IKeyboardController
{
public:
    virtual KeyDirection getKeyboardInput();
    virtual bool wasExitKeyPressed();
};

#endif  // KEYBOARD_CONTROLLER_HPP_