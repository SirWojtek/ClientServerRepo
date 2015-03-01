#ifndef UPDATE_PLAYER_HPP_
#define UPDATE_PLAYER_HPP_

#include <string>
#include <cereal/types/utility.hpp>

namespace common
{

struct UpdatePlayer
{
    std::pair<int, int> delta;
    int actionId;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(type()), CEREAL_NVP(delta), CEREAL_NVP(actionId));
    }

    static std::string type()
    {
        return std::string("UpdatePlayer");
    }
};

}

#endif  // UPDATE_PLAYER_HPP_
