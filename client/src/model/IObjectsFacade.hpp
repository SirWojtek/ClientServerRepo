#ifndef IOBJECTS_FACADE_HPP_
#define IOBJECTS_FACADE_HPP_

#include "model/Object.hpp"

namespace model
{

class IObjectsFacade
{
public:
    virtual void addActiveObject(const Object& obj) = 0;
    virtual void addInactiveObject(const Object& obj) = 0;
};

}

#endif  // IOBJECTS_FACADE_HPP_
