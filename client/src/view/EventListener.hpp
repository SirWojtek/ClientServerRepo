#ifndef EVENT_LISTENER_HPP_
#define EVENT_LISTENER_HPP_

#include <map>
#include <functional>

#include <SFML/Window/Event.hpp>

namespace view
{

class EventListener
{
public:
	using CallbackFunc = std::function<void(const sf::Event&)>;

    static void subscribe(sf::Event::EventType type, CallbackFunc callback);
    static void receiveEvent(const sf::Event& event);

private:
    static std::map<sf::Event::EventType, CallbackFunc> subscribeMap;
};

}

#endif  // EVENT_LISTENER_HPP_
