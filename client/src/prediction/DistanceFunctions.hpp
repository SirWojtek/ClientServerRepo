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
    float startPointsDistanceAndDirection(const InputRecord& comp) const;
    float weightStartPointsDistanceAndDirection(const InputRecord& comp) const;
    float reversedWeightStartPointsDistanceAndDirection(const InputRecord& comp) const;
    float directionDistance(const InputRecord& comp) const;

    static void setWeight(float newWeight);

private:
    InputRecord input;
    static float weight;
};

}

#endif  // DISTANCE_FUNCTIONS_HPP_
