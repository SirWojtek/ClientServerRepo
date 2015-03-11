#ifndef IOBJECTS_FACADE_HPP_
#define IOBJECTS_FACADE_HPP_

#include "objects/Object.hpp"

#include "common/maps/IMapContainer.hpp"

namespace model
{

class IObjectsFacade
{
public:
    virtual void loadMaps() = 0;
    virtual void addActiveObject(const Object& obj) = 0;
    virtual void addInactiveObject(const Object& obj) = 0;
    virtual ObjectPtr getPlayerObject() = 0;
    virtual maps::MapContainerPtr getCurrentMap() const = 0;
};
using ObjectsFacadePtr = std::shared_ptr<IObjectsFacade>;

}

#endif  // IOBJECTS_FACADE_HPP_
