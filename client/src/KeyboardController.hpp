#ifndef KEYBOARD_CONTROLLER_HPP_
#define KEYBOARD_CONTROLLER_HPP_

#include <map>
#include <mutex>
#include <vector>

#include "IKeyboardController.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class KeyboardController : public IKeyboardController
{
    struct ThreadSafeEvent
    {
        std::vector<sf::Keyboard::Key> keyVector;
        std::mutex mutex;
    };

public:
    KeyboardController();

    virtual KeyDirection getKeyboardInput();
    virtual bool wasExitKeyPressed();
    virtual void keyCallback(const sf::Event&);

private:
    void processKeyPressed(const sf::Event&);
    void processKeyReleased(const sf::Event&);
    sf::Keyboard::Key getPressedKey();

    std::map<sf::Keyboard::Key, KeyDirection> keyMapping_;
    ThreadSafeEvent safeEvent_;
    bool wasExitKeyPressed_ = false;

    static const sf::Keyboard::Key noKeyPressed;
};

#endif  // KEYBOARD_CONTROLLER_HPP_
