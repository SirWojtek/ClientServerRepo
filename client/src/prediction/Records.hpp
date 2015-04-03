#ifndef RECORDS_HPP_
#define RECORDS_HPP_

#include <vector>
#include <utility>

namespace prediction
{

struct DeltaRecord
{
    DeltaRecord();
    DeltaRecord(unsigned deltaX, unsigned deltaY);
    DeltaRecord(const std::vector<std::pair<unsigned, unsigned>>& dataVector);

    bool operator<(const DeltaRecord& a) const;

    unsigned deltaX, deltaY;
};

struct InputRecord
{
    InputRecord();
    InputRecord(const std::vector<std::pair<unsigned, unsigned>>& dataVector);

    bool operator<(const InputRecord& a) const;

    unsigned beginX, beginY;
    std::vector<DeltaRecord> steps;
};


}

#endif  // RECORDS_HPP_
