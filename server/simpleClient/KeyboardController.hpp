#ifndef KEYBOARD_CONTROLLER_HPP_
#define KEYBOARD_CONTROLLER_HPP_

#include "IKeyboardController.hpp"
#include "IKeyGetter.hpp"

class KeyboardController : public IKeyboardController
{
public:
    KeyboardController(KeyGetterPtr keyGetter);

    virtual KeyDirection getKeyboardInput();
    virtual bool wasExitKeyPressed();

private:
    KeyGetterPtr keyGetter_;
    bool wasExitKeyPressed_ = false;
};

#endif  // KEYBOARD_CONTROLLER_HPP_
