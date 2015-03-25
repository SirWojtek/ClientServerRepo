
#include "KeyboardController.hpp"

#include <functional>
#include <stdexcept>
#include <algorithm>

#include "view/EventListener.hpp"

const sf::Keyboard::Key KeyboardController::noKeyPressed = sf::Keyboard::Key::Unknown;

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
        std::bind(&KeyboardController::keyCallback, this, _1));
    view::EventListener::subscribe(sf::Event::KeyReleased,
        std::bind(&KeyboardController::keyCallback, this, _1));

    safeEvent_.keyVector.emplace_back(noKeyPressed);
}

KeyboardController::KeyDirection KeyboardController::getKeyboardInput()
{
    sf::Keyboard::Key key = getPressedKey();

    auto foundKeyIt = keyMapping_.find(key);

    if (foundKeyIt == keyMapping_.end() || key == noKeyPressed)
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

void KeyboardController::keyCallback(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        processKeyPressed(event);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        processKeyReleased(event);
    }
    else
    {
        throw std::runtime_error("Unknown type of event received");
    }
}

void KeyboardController::processKeyPressed(const sf::Event& event)
{
    std::unique_lock<std::mutex> lock(safeEvent_.mutex);

    auto it = std::find(safeEvent_.keyVector.begin(), safeEvent_.keyVector.end(), event.key.code);

    if (it == safeEvent_.keyVector.end())
    {
        safeEvent_.keyVector.emplace_back(event.key.code);
    }
}

void KeyboardController::processKeyReleased(const sf::Event& event)
{
    std::unique_lock<std::mutex> lock(safeEvent_.mutex);

    auto it = std::find(safeEvent_.keyVector.begin(), safeEvent_.keyVector.end(), event.key.code);

    if (it == safeEvent_.keyVector.end())
    {
        return;
    }

    safeEvent_.keyVector.erase(it);
}

sf::Keyboard::Key KeyboardController::getPressedKey()
{
    std::unique_lock<std::mutex> lock(safeEvent_.mutex);
    return safeEvent_.keyVector.back();
}