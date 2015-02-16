#ifndef MODEL_STONE_OBJECT_HPP_
#define MODEL_STONE_OBJECT_HPP_

#include "Object.hpp"

#include <string>

namespace model
{

class StoneObject : public Object
{
public:
    void getTexture();
    std::string getDescription();
};
}

#endif  // MODEL_STONE_OBJECT_HPP_