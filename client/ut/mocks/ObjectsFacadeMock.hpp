#ifndef OBJECTS_FACADE_MOCK_HPP_
#define OBJECTS_FACADE_MOCK_HPP_

#include <memory>
#include <gmock/gmock.h>

#include "client/src/model/IObjectsFacade.hpp"
#include "client/src/model/objects/Object.hpp"

#include "common/maps/IMapContainer.hpp"

class ObjectsFacadeMock : public model::IObjectsFacade
{
public:
    MOCK_METHOD0(loadMaps, void());
    MOCK_METHOD1(addActiveObject, void(const model::Object& obj));
    MOCK_METHOD1(addInactiveObject, void(const model::Object& obj));
    MOCK_METHOD0(getPlayerObject, model::ObjectPtr());
    MOCK_CONST_METHOD0(getCurrentMap, maps::MapContainerPtr());
};
using ObjectsFacadeMockPtr = std::shared_ptr<ObjectsFacadeMock>;

#endif  // OBJECTS_FACADE_MOCK_HPP_

