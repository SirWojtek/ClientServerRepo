#ifndef OBJECTS_FACADE_HPP_
#define OBJECTS_FACADE_HPP_

#include "IObjectsFacade.hpp"
#include <set>
#include "objects/Object.hpp"

namespace model
{

class ObjectsFacade : IObjectsFacade
{
public:
    ObjectsFacade();

    void addActiveObject(const Object& obj);
    void addInactiveObject(const Object& obj);
    ObjectPtr getPlayerObject();

private:
    ObjectPtr playerObject_;
    std::set<ObjectPtr> activeObjects_;
    std::set<ObjectPtr> inactiveObjects_;
};

}

#endif  // OBJECTS_FACADE_HPP_
