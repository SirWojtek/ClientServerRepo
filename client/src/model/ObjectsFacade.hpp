#ifndef OBJECTS_FACADE_HPP_
#define OBJECTS_FACADE_HPP_

#include "IObjectsFacade.hpp"
#include <set>
#include "objects/Object.hpp"

namespace model
{

class ObjectsFacade : public IObjectsFacade
{
public:
    ObjectsFacade();

    virtual void addActiveObject(const Object& obj);
    virtual void addInactiveObject(const Object& obj);
    virtual ObjectPtr getPlayerObject();

private:
    ObjectPtr playerObject_;
    std::set<ObjectPtr> activeObjects_;
    std::set<ObjectPtr> inactiveObjects_;
};

}

#endif  // OBJECTS_FACADE_HPP_
