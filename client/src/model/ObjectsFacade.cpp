
#include "ObjectsFacade.hpp"
#include <set>
#include "model/Object.hpp"

namespace model
{

void ObjectsFacade::addActiveObject(const Object& obj)
{
    activeObjects_.insert(obj);
}

void ObjectsFacade::addInactiveObject(const Object& obj)
{
    inactiveObjects_.insert(obj);
}

}

#endif  // OBJECTS_FACADE_HPP_
