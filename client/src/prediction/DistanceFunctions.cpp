
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
    return std::abs(comp.direction.deltaX - input.direction.deltaX) +
        std::abs(comp.direction.deltaY - input.direction.deltaY);
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

}
