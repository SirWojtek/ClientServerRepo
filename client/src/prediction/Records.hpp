#ifndef RECORDS_HPP_
#define RECORDS_HPP_

#include <vector>

namespace prediction
{

struct DeltaRecord
{
    unsigned deltaX, deltaY;
};

struct InputRecord
{
    unsigned beginX, beginY;
    std::vector<DeltaRecord> steps;
};


}

#endif  // RECORDS_HPP_
