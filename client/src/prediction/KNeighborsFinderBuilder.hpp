#ifndef K_NEIGHBORS_FINDER_BUILDER_HPP_
#define K_NEIGHBORS_FINDER_BUILDER_HPP_

#include "KNeighborsFinder.hpp"
#include "Records.hpp"

#include <vector>
#include <string>
#include <functional>

namespace prediction
{

using BasicKNeighborFinder = KNeighborsFinder<InputRecord, DeltaRecord>;
using FileVector = std::vector<std::string>;

BasicKNeighborFinder buildKNeighborsFinder(const FileVector& dataFile,
    unsigned recordSize, std::function<int(const InputRecord&)> distFunc);

}

#endif  // K_NEIGHBORS_FINDER_BUILDER_HPP_
