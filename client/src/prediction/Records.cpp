
#include "Records.hpp"

#include <tuple>

namespace prediction
{

DeltaRecord::DeltaRecord() {}

DeltaRecord::DeltaRecord(int deltaX, int deltaY) :
    deltaX(deltaX),
    deltaY(deltaY) {}

DeltaRecord::DeltaRecord(const std::vector<std::pair<int, int>>& data) :
    deltaX(data[data.size() - 1].first - data[data.size() - 2].first),
    deltaY(data[data.size() - 1].second - data[data.size() - 2].second) {}

bool DeltaRecord::operator<(const DeltaRecord& a) const
{
    return std::tie(deltaX, deltaY) < std::tie(a.deltaX, a.deltaY);
}

bool DeltaRecord::operator==(const DeltaRecord& a) const
{
    return deltaX == a.deltaX && deltaY == a.deltaY;
}

std::ostream& operator<<(std::ostream& stream, const DeltaRecord& x)
{
    return stream << "( " << x.deltaX << " , " << x.deltaY << ")";
}

InputRecord::InputRecord() {}

InputRecord::InputRecord(const std::vector<std::pair<int, int>>& dataVector) :
    beginX(dataVector[0].first),
    beginY(dataVector[0].second)
{
    int prevStepX = beginX;
    int prevStepY = beginY;

    for (unsigned i = 1; i < dataVector.size() - 1; i++)
    {
        int stepX = dataVector[i].first - prevStepX;
        int stepY = dataVector[i].second - prevStepY;

        steps.emplace_back(stepX, stepY);

        prevStepX = dataVector[i].first;
        prevStepY = dataVector[i].second;
    }
}

bool InputRecord::operator<(const InputRecord& a) const
{
    return std::tie(beginX, beginY, steps) < std::tie(a.beginX, a.beginY, a.steps);
}

std::ostream& operator<<(std::ostream& stream, const InputRecord& x)
{
    stream << "( " << x.beginX << " , " << x.beginY << ") -> ";

    for (unsigned i = 0; i < x.steps.size() - 1; i++)
    {
        stream << x.steps[i] << " -> ";
    }
    stream << x.steps.back();

    return stream;
}

}
