#ifndef NO_CHANGES_HPP_
#define NO_CHANGES_HPP_

#include <cereal/types/utility.hpp>

namespace common
{

struct NoChanges
{
    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(type());
    }

    static std::string type()
    {
        return std::string("NoChanges");
    }
};

}

#endif