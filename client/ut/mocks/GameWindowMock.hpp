#ifndef GAME_WINDOW_MOCK_HPP_
#define GAME_WINDOW_MOCK_HPP_

#include <gmock/gmock.h>
#include <memory>

#include "client/src/view/IGameWindow.hpp"

class GameWindowMock : public view::IGameWindow
{
public:
    MOCK_METHOD0(startWindowThread, void());
    MOCK_METHOD0(tearDown, void());
};
using GameWindowMockPtr = std::shared_ptr<GameWindowMock>;

#endif  // GAME_WINDOW_MOCK_HPP_
