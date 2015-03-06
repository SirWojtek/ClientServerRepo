
#include "EventListener.hpp"

#include <map>
#include <functional>
#include <stdexcept>
#include <utility>

#include <SFML/Window/Event.hpp>

namespace view
{
using CallbackFunc = std::function<void(sf::Event)>;

std::map<sf::Event::EventType, CallbackFunc> EventListener::subscribeMap;

void EventListener::subscribe(sf::Event::EventType type, CallbackFunc callback)
{
    if (subscribeMap.find(type) != subscribeMap.end())
    {
        throw std::runtime_error("Another callback already subscribed for event");
    }

    subscribeMap.insert(std::make_pair(type, callback));
}

void EventListener::receiveEvent(sf::Event event)
{
    auto it = subscribeMap.find(event.type);

    if (it != subscribeMap.end())
    {
        it->second(event);
    }
}

}
