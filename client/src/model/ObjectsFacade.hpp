#ifndef OBJECTS_FACADE_HPP_
#define OBJECTS_FACADE_HPP_

#include "IObjectsFacade.hpp"

#include <set>
#include <vector>
#include <string>

#include "objects/Object.hpp"

namespace model
{

class ObjectsFacade : public IObjectsFacade
{
public:
    ObjectsFacade();

    void loadMaps();
    void addActiveObject(const Object& obj);
    void addInactiveObject(const Object& obj);
    ObjectPtr getPlayerObject();
    maps::IMapContainer& getCurrentMap();

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
