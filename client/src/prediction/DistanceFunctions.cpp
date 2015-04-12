
#include "DistanceFunctions.hpp"
#include "Records.hpp"

#include <complex>
#include <algorithm>

namespace prediction
{

float DistanceFunctions::weight = 0.3;

void DistanceFunctions::setWeight(float newWeight)
{
    weight = newWeight;
}

void DistanceFunctions::setInput(const InputRecord& input)
{
    this->input = input;
}

float DistanceFunctions::startPointsDistance(const InputRecord& comp) const
{
    return std::abs(comp.beginX - input.beginX) +
        std::abs(comp.beginY - input.beginY);
}

float DistanceFunctions::directionDistance(const InputRecord& comp) const
{
    Sums sums = getSumedDeltas(comp);

    return std::abs(sums.inputSum.deltaX - sums.compSum.deltaX) +
        std::abs(sums.inputSum.deltaY - sums.compSum.deltaY);
}

float DistanceFunctions::startPointsDistanceAndDirection(const InputRecord& comp) const
{
    return startPointsDistance(comp) + directionDistance(comp);
}

float DistanceFunctions::weightStartPointsDistanceAndDirection(const InputRecord& comp) const
{
    return weight * startPointsDistance(comp) + (1.0f - weight) * directionDistance(comp);
}

float DistanceFunctions::reversedWeightStartPointsDistanceAndDirection(
    const InputRecord& comp) const
{
    return weight * directionDistance(comp) + (1.0f - weight) * startPointsDistance(comp);
}

DistanceFunctions::Sums DistanceFunctions::getSumedDeltas(const InputRecord& comp) const
{
    Sums result;

    result.compSum = std::accumulate(comp.steps.begin(), comp.steps.end(), DeltaRecord());
    result.inputSum = std::accumulate(
        input.steps.begin(), input.steps.end(), DeltaRecord());

    return result; 
}


}
