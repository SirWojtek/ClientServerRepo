#ifndef RECORDS_HPP_
#define RECORDS_HPP_

#include <utility>
#include <ostream>
#include <vector>

namespace prediction
{

struct DeltaRecord
{
    DeltaRecord();
    DeltaRecord(int deltaX, int deltaY);
    DeltaRecord(const std::vector<std::pair<int, int>>& dataVector);

    bool operator<(const DeltaRecord& a) const;
    bool operator==(const DeltaRecord& a) const;
    DeltaRecord operator+(const DeltaRecord& a) const;

    int deltaX, deltaY;
};

std::ostream& operator<<(std::ostream& stream, const DeltaRecord& x);

struct InputRecord
{
    InputRecord();
    InputRecord(const std::vector<std::pair<int, int>>& dataVector);

    bool operator<(const InputRecord& a) const;

    int beginX, beginY;
    DeltaRecord direction;
};

std::ostream& operator<<(std::ostream& stream, const InputRecord& x);

}

#endif  // RECORDS_HPP_
