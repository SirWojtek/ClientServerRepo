#ifndef LOGIN_HPP_
#define LOGIN_HPP_

#include <string>
#include <cereal/types/utility.hpp>

namespace common
{

/* Client identifies itself to the Server */

struct Login
{
    std::string playerName;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(type()), CEREAL_NVP(playerName));
    }

    static std::string type()
    {
        return std::string("Login");
    }
};

}

#endif  // LOGIN_HPP_
