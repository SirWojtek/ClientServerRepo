
#include "Object.hpp"

#include <tuple>

#include "common/utilities/NotImplementedException.hpp"

namespace model
{

Object::Object(bool isStatic) :
    position({0, 0}),
    isStatic(isStatic) {}

Object::Object(Position position, bool isStatic) :
    position(position),
    isStatic(isStatic) {}

void Object::getTexture() const
{
    throw NotImplementedException();
}

std::string Object::getDescription() const
{
    throw NotImplementedException();
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
