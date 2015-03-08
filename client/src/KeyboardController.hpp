#ifndef KEYBOARD_CONTROLLER_HPP_
#define KEYBOARD_CONTROLLER_HPP_

#include <map>
#include <mutex>
#include <condition_variable>

#include "IKeyboardController.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class KeyboardController : public IKeyboardController
{
    struct ThreadSafeEvent
    {
        sf::Event event;
        std::mutex mutex;
        std::condition_variable conditional;
    };

public:
    KeyboardController();

    virtual KeyDirection getKeyboardInput();
    virtual bool wasExitKeyPressed();
    virtual void keyPressedCallback(const sf::Event&);

private:
    void getPressedKey();

    std::map<sf::Keyboard::Key, KeyDirection> keyMapping_;
    ThreadSafeEvent safeEvent_;
    bool wasExitKeyPressed_ = false;

    static const sf::Event::EventType emptyEvent = sf::Event::EventType::Count;
};

#endif  // KEYBOARD_CONTROLLER_HPP_
