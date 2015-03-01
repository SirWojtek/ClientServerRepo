#ifndef UPDATE_ENVIRONMENT_HPP_
#define UPDATE_ENVIRONMENT_HPP_

#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

namespace common
{

struct UpdateEnvironment
{
    struct Changes
    {
        int state;
        std::pair<int, int> delta;
        int id;

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(CEREAL_NVP(state), CEREAL_NVP(delta), CEREAL_NVP(id));
        }
    };

    std::vector<Changes> changesVector;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(getName()), CEREAL_NVP(changesVector));
    }

    static std::string getName()
    {
        return std::string("UpdateEnvironment");
    }
};

}


#endif  // UPDATE_ENVIRONMENT_HPP_
