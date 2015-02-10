#ifndef UPDATE_ENVIRONMENT_HPP_
#define UPDATE_ENVIRONMENT_HPP_

#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>

namespace common
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

struct UpdateEnvironment
{
    std::vector<Changes> changesVector;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(type), CEREAL_NVP(changesVector));
    }

private:
    std::string type = "UpdateEnvironment";
};

}


#endif  // UPDATE_ENVIRONMENT_HPP_
