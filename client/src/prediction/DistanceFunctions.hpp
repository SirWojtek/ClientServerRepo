#ifndef DISTANCE_FUNCTIONS_HPP_
#define DISTANCE_FUNCTIONS_HPP_

#include "Records.hpp"

namespace prediction
{

class DistanceFunctions
{
public:
    void setInput(const InputRecord& input);
    float startPointsDistance(const InputRecord& comp) const;

private:
    InputRecord input;
};

}

#endif  // DISTANCE_FUNCTIONS_HPP_