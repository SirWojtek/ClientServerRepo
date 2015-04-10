
#include "DistanceFunctions.hpp"
#include "Records.hpp"

#include <complex>
#include <algorithm>

namespace prediction
{

void DistanceFunctions::setInput(const InputRecord& input)
{
    this->input = input;
}

float DistanceFunctions::startPointsDistance(const InputRecord& comp) const
{
    DeltaRecord sum = std::accumulate(comp.steps.begin(), comp.steps.end(), DeltaRecord());

    return std::abs(comp.beginX + sum.deltaX - input.beginX) +
        std::abs(comp.beginY + sum.deltaY - input.beginY);
}

}
