
#include "Object.hpp"

#include <tuple>

namespace model
{

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
