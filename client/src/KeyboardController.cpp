
#include "KeyboardController.hpp"
#include <istream>

KeyboardController::KeyboardController(std::istream& keyboardStream) :
    keyboardStream_(keyboardStream) {}

KeyboardController::KeyDirection KeyboardController::getKeyboardInput()
{
    char pressedKey = keyboardStream_.get();

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
