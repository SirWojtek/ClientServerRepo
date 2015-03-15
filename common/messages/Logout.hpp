#ifndef LOGOUT_HPP_
#define LOGOUT_HPP_

#include <string>
#include <cereal/types/utility.hpp>

namespace common
{

/* Client informs Server that he is logging out */

struct Logout
{
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(type()));
    }

    static std::string type()
    {
        return std::string("Logout");
    }
};

}

#endif  // LOGOUT_HPP_
