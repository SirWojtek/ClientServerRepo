#ifndef RECORDS_HPP_
#define RECORDS_HPP_

#include <vector>
#include <utility>

namespace prediction
{

struct DeltaRecord
{
    DeltaRecord();
    DeltaRecord(int deltaX, int deltaY);
    DeltaRecord(const std::vector<std::pair<int, int>>& dataVector);

    bool operator<(const DeltaRecord& a) const;

    int deltaX, deltaY;
};

struct InputRecord
{
    InputRecord();
    InputRecord(const std::vector<std::pair<int, int>>& dataVector);

    bool operator<(const InputRecord& a) const;

    int beginX, beginY;
    std::vector<DeltaRecord> steps;
};


}

#endif  // RECORDS_HPP_
