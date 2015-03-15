
#include "Object.hpp"

#include <tuple>

#include <SFML/Graphics/Rect.hpp>

#include "common/utilities/NotImplementedException.hpp"

namespace model
{

Object::Object(bool isStatic) :
    position({0, 0}),
    isStatic(isStatic) {}

Object::Object(Position position, unsigned size, bool isStatic) :
    position(position),
    size(size),
    isStatic(isStatic) {}

void Object::getTexture() const
{
    throw NotImplementedException();
}

std::string Object::getDescription() const
{
    throw NotImplementedException();
}

sf::FloatRect Object::getPositionRect() const
{
    sf::FloatRect rect;
    
    rect.left = position.x;
    rect.top = position.y;
    rect.width = size;
    rect.height = size;

    return rect;
}

bool Object::operator<(const Object& a) const
{
    return std::tie(position.x, position.y, isStatic) <
        std::tie(a.position.x, a.position.y, a.isStatic);
}

bool Object::operator>(const Object& a) const
{
    return std::tie(position.x, position.y, isStatic) >
        std::tie(a.position.x, a.position.y, a.isStatic);
}

bool Object::operator==(const Object& a) const
{
    return std::tie(position.x, position.y, isStatic) ==
        std::tie(a.position.x, a.position.y, a.isStatic);
}

bool Object::operator!=(const Object& a) const
{
    return !(*this == a);
}

}
