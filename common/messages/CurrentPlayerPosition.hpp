#ifndef CURRENT_PLAYER_POSITION_HPP_
#define CURRENT_PLAYER_POSITION_HPP_

#include <string>
#include <cereal/types/utility.hpp>
#include <cereal/types/tuple.hpp>

namespace common
{

/* After identifying Client, Server sends him his current position */

struct CurrentPlayerPosition
{
    std::tuple<int, int, int> position;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(type()), CEREAL_NVP(position));
    }

    static std::string type()
    {
        return std::string("CurrentPlayerPosition");
    }
};

}

#endif  // CURRENT_PLAYER_POSITION_HPP_
