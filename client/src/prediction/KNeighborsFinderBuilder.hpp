#ifndef K_NEIGHBORS_FINDER_BUILDER_HPP_
#define K_NEIGHBORS_FINDER_BUILDER_HPP_

#include "KNeighborsFinder.hpp"
#include "Records.hpp"
#include "PredictionDefinitions.hpp"

#include <functional>

namespace prediction
{

BasicKNeighborFinder buildKNeighborsFinder(const FileVector& dataFile,
    unsigned recordSize, std::function<float(const InputRecord&)> distFunc);

std::vector<DataVector> getPartitionedData(const FileVector& dataFiles, unsigned recordSize);

}

#endif  // K_NEIGHBORS_FINDER_BUILDER_HPP_
