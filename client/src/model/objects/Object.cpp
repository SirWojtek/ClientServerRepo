
#include "Object.hpp"

#include <tuple>

namespace model
{

Object::Object() :
    position({0, 0}),
    isStatic(false) {}

Object::Object(bool isStatic) :
    position({0, 0}),
    isStatic(isStatic) {}

Object::Object(Position position) :
    position(position),
    isStatic(false) {}

Object::Object(Position position, bool isStatic) :
    position(position),
    isStatic(isStatic) {}

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
