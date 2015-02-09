#ifndef UPDATE_ENVIRONMENT_HPP_
#define UPDATE_ENVIRONMENT_HPP_

#include <vector>
#include <utility>

namespace common
{

struct Changes
{
    int state;
    std::pair<int, int> delta;
    int id;
};

struct UpdateEnvironment
{
    std::vector<Changes> changesVector;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(type, changesVector);
    }

private:
    std::string type = "UpdateEnvironment";
};

}

#endif  // UPDATE_ENVIRONMENT_HPP_
