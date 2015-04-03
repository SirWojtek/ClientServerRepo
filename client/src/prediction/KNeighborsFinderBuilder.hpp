#ifndef K_NEIGHBORS_FINDER_BUILDER_HPP_
#define K_NEIGHBORS_FINDER_BUILDER_HPP_

#include "KNeighborsFinder.hpp"
#include "Records.hpp"

#include <string>
#include <functional>

namespace prediction
{

KNeighborsFinder<InputRecord, DeltaRecord> buildKNeighborsFinder(const std::string& dataFile,
    unsigned recordSize, std::function<unsigned(InputRecord)> distFunc);

}

#endif  // K_NEIGHBORS_FINDER_BUILDER_HPP_
