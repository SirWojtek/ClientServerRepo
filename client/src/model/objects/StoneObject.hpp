#ifndef MODEL_STONE_OBJECT_HPP_
#define MODEL_STONE_OBJECT_HPP_

#include "Object.hpp"

#include <string>

namespace model
{

class StoneObject : public Object
{
public:
    void getTexture() const;
    std::string getDescription() const;
};
}

#endif  // MODEL_STONE_OBJECT_HPP_