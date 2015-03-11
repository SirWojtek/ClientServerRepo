#ifndef OBJECTS_FACADE_HPP_
#define OBJECTS_FACADE_HPP_

#include "IObjectsFacade.hpp"

#include <set>
#include <vector>
#include <string>

#include "objects/Object.hpp"

#include "common/maps/IMapContainer.hpp"

namespace model
{

class ObjectsFacade : public IObjectsFacade
{
public:
    ObjectsFacade();

    virtual void loadMaps();
    virtual void addActiveObject(const Object& obj);
    virtual void addInactiveObject(const Object& obj);
    virtual ObjectPtr getPlayerObject();
    virtual maps::MapContainerPtr getCurrentMap() const;

private:
    ObjectPtr playerObject_;
    std::set<ObjectPtr> activeObjects_;
    std::set<ObjectPtr> inactiveObjects_;
    std::vector<maps::MapContainerPtr> maps_;

    static const std::vector<std::string> mapFiles;
    static const std::string mapPath;
};

}

#endif  // OBJECTS_FACADE_HPP_
