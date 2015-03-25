#include <gtest/gtest.h>
#include <memory>

#include "client/src/KeyboardController.hpp"
#include "client/src/view/EventListener.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace ::testing;

struct KeyToDirection
{
    sf::Keyboard::Key key;
    KeyboardController::KeyDirection direction;
};

class KeyboardControllerShould : public TestWithParam<KeyToDirection>
{
protected:
    KeyboardControllerShould() :
        keyboardController_(std::make_shared<KeyboardController>())
    {}

    void SetUp()
    {
        view::EventListener::reset();
    }

    sf::Event createEvent(const sf::Keyboard::Key& key)
    {
        sf::Event event;
        event.type = sf::Event::KeyPressed;
        event.key.code = key;

        return event;
    }

    KeyboardControllerPtr keyboardController_;
};

TEST_P(KeyboardControllerShould, returnCorrectDirection)
{
    KeyToDirection param = GetParam();
    sf::Event event = createEvent(param.key);

    keyboardController_->keyCallback(event);

    EXPECT_EQ(keyboardController_->getKeyboardInput(), param.direction);
    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), false);
}

INSTANTIATE_TEST_CASE_P(keyCombinations, KeyboardControllerShould, Values(
        KeyToDirection({sf::Keyboard::Key::W, KeyboardController::Up}),
        KeyToDirection({sf::Keyboard::Key::Up, KeyboardController::Up}),
        KeyToDirection({sf::Keyboard::Key::S, KeyboardController::Down}),
        KeyToDirection({sf::Keyboard::Key::Down, KeyboardController::Down}),
        KeyToDirection({sf::Keyboard::Key::D, KeyboardController::Right}),
        KeyToDirection({sf::Keyboard::Key::Right, KeyboardController::Right}),
        KeyToDirection({sf::Keyboard::Key::A, KeyboardController::Left}),
        KeyToDirection({sf::Keyboard::Key::Left, KeyboardController::Left}),
        KeyToDirection({sf::Keyboard::Key::J, KeyboardController::None})
));

TEST_F(KeyboardControllerShould, returnTrueIfExitKeyWasPressed)
{
    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), false);

    sf::Event event = createEvent(sf::Keyboard::Key::Escape);
    keyboardController_->keyCallback(event);

    EXPECT_EQ(keyboardController_->getKeyboardInput(), KeyboardController::None);
    EXPECT_EQ(keyboardController_->wasExitKeyPressed(), true);
}
