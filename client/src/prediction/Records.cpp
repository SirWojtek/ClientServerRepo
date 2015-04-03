
#include "Records.hpp"

#include <tuple>

namespace prediction
{

DeltaRecord::DeltaRecord() {}

DeltaRecord::DeltaRecord(unsigned deltaX, unsigned deltaY) :
    deltaX(deltaX),
    deltaY(deltaY) {}

DeltaRecord::DeltaRecord(const std::vector<std::pair<unsigned, unsigned>>& data) :
    deltaX(data[data.size() - 1].first - data[data.size() - 2].first),
    deltaY(data[data.size() - 1].second - data[data.size() - 2].second) {}

bool DeltaRecord::operator<(const DeltaRecord& a) const
{
    return std::tie(deltaX, deltaY) < std::tie(a.deltaX, a.deltaY);
}

InputRecord::InputRecord() {}

InputRecord::InputRecord(const std::vector<std::pair<unsigned, unsigned>>& dataVector) :
    beginX(dataVector[0].first),
    beginY(dataVector[0].second)
{
    unsigned prevStepX = beginX;
    unsigned prevStepY = beginY;

    for (unsigned i = 1; i < dataVector.size() - 1; i++)
    {
        unsigned stepX = dataVector[i].first - prevStepX;
        unsigned stepY = dataVector[i].second - prevStepY;

        steps.emplace_back(stepX, stepY);

        prevStepX = dataVector[i].first;
        prevStepY = dataVector[i].second;
    }
}

bool InputRecord::operator<(const InputRecord& a) const
{
    return std::tie(beginX, beginY, steps) < std::tie(a.beginX, a.beginY, a.steps);
}

}
