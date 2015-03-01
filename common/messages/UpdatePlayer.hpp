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
        archive(getName(), delta, actionId);
    }

    static std::string getName()
    {
        return std::string("UpdatePlayer");
    }
};

}

#endif  // UPDATE_PLAYER_HPP_
