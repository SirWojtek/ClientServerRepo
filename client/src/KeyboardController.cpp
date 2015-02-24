
#include "KeyboardController.hpp"
#include "IKeyGetter.hpp"

#include <curses.h>

KeyboardController::KeyboardController(KeyGetterPtr keyGetter) :
    keyGetter_(keyGetter) {}

KeyboardController::KeyDirection KeyboardController::getKeyboardInput()
{
    char pressedKey = keyGetter_->getPressedKey();

    switch(pressedKey)
    {
        case 'w':
            return Up;
        case 's':
            return Down;
        case 'd':
            return Right;
        case 'a':
            return Left;
        case 'q':
            wasExitKeyPressed_ = true;
        default:
            return None;
    }
}

bool KeyboardController::wasExitKeyPressed()
{
    return wasExitKeyPressed_;
}
