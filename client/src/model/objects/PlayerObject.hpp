#ifndef MODEL_PLAYER_OBJECT_HPP_
#define MODEL_PLAYER_OBJECT_HPP_

#include "Object.hpp"

#include <string>

namespace model
{

class PlayerObject : public Object
{
public:
    void getTexture() const;
    std::string getDescription() const;
};
}

#endif  // MODEL_PLAYER_OBJECT_HPP_