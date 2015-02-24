#ifndef KEYBOARD_CONTROLLER_MOCK_HPP_
#define KEYBOARD_CONTROLLER_MOCK_HPP_

#include <memory>
#include <gmock/gmock.h>


#include "client/src/IKeyboardController.hpp"

class KeyboardControllerMock : public IKeyboardController
{
public:
    MOCK_METHOD0(getKeyboardInput, KeyDirection());
    MOCK_METHOD0(wasExitKeyPressed, bool());
};
using KeyboardControllerMockPtr = std::shared_ptr<KeyboardControllerMock>;

#endif  // KEYBOARD_CONTROLLER_MOCK_HPP_
