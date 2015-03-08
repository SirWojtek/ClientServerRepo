
#include "KeyboardController.hpp"

#include <functional>
#include <mutex>
#include <condition_variable>

#include "view/EventListener.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

KeyboardController::KeyboardController() :
    keyMapping_(
    {
        {sf::Keyboard::Key::W, Up}, {sf::Keyboard::Key::Up, Up},
        {sf::Keyboard::Key::S, Down}, {sf::Keyboard::Key::Down, Down},
        {sf::Keyboard::Key::A, Left}, {sf::Keyboard::Key::Left, Left},
        {sf::Keyboard::Key::D, Right}, {sf::Keyboard::Key::Right, Right},
        {sf::Keyboard::Key::Q, Exit}, {sf::Keyboard::Key::Escape, Exit}
    })
{
    using namespace std::placeholders;
    view::EventListener::subscribe(sf::Event::KeyPressed,
        std::bind(&KeyboardController::keyPressedCallback, this, _1));
}

KeyboardController::KeyDirection KeyboardController::getKeyboardInput()
{
    getPressedKey();

    auto foundKeyIt = keyMapping_.find(safeEvent_.event.key.code);

    if (foundKeyIt == keyMapping_.end())
    {
        return None;
    }
    else if (foundKeyIt->second == Exit)
    {
        wasExitKeyPressed_ = true;
        return None;
    }
    else
    {
        return foundKeyIt->second;
    }
}

bool KeyboardController::wasExitKeyPressed()
{
    return wasExitKeyPressed_;
}

void KeyboardController::keyPressedCallback(const sf::Event& event)
{
    std::unique_lock<std::mutex> lock(safeEvent_.mutex);
    
    while (safeEvent_.event.type != emptyEvent)
        safeEvent_.conditional.wait(lock);

    safeEvent_.event = event;
    safeEvent_.conditional.notify_one();
}

void KeyboardController::getPressedKey()
{
    std::unique_lock<std::mutex> lock(safeEvent_.mutex);

    while (safeEvent_.event.type == emptyEvent)
        safeEvent_.conditional.wait(lock);

    safeEvent_.event.type = emptyEvent;
    safeEvent_.conditional.notify_one();
}