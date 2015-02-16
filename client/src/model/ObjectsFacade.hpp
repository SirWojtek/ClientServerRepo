#ifndef OBJECTS_FACADE_HPP_
#define OBJECTS_FACADE_HPP_

#include "IObjectsFacade.hpp"
#include <set>
#include "model/Object.hpp"

namespace model
{

class ObjectsFacade : IObjectsFacade
{
public:
    void addActiveObject(const Object& obj);
    void addInactiveObject(const Object& obj);

private:
    std::set<Object> activeObjects_;
    std::set<Object> inactiveObjects_;
};

}

#endif  // OBJECTS_FACADE_HPP_
