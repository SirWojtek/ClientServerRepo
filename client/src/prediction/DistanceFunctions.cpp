
#include "DistanceFunctions.hpp"
#include "Records.hpp"

#include <complex>

namespace prediction
{

void DistanceFunctions::setInput(const InputRecord& input)
{
    this->input = input;
}

float DistanceFunctions::startPointsDistance(const InputRecord& comp) const
{
    return std::abs(comp.beginX - input.beginX) + std::abs(comp.beginY - input.beginY);
}

}
