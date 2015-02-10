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
        archive(type, delta, actionId);
    }

private:
    std::string type = "UpdatePlayer";
};

}

#endif  // UPDATE_PLAYER_HPP_
