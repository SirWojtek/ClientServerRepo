#ifndef KEYBOARD_CONTROLLER_HPP_
#define KEYBOARD_CONTROLLER_HPP_

#include "IKeyboardController.hpp"
#include <istream>

class KeyboardController : public IKeyboardController
{
public:
    KeyboardController(std::istream& keyboardStream);

    virtual KeyDirection getKeyboardInput();
    virtual bool wasExitKeyPressed();

private:
    std::istream& keyboardStream_;
    bool wasExitKeyPressed_ = false;
};

#endif  // KEYBOARD_CONTROLLER_HPP_