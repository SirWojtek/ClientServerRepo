
#include "DirectionChooseFunctions.hpp"
#include "Records.hpp"

#include <algorithm>

namespace prediction
{

DeltaRecord getClosestNeighborDirectionWithMaxOccurence(
    const BasicKNeighborFinder::NeighborsVector& neighbors)
{
    BasicKNeighborFinder::OutputHistogram histogram = neighbors[0].second;

    auto bestMatch = std::max_element(histogram.begin(), histogram.end(),
        [](const std::pair<DeltaRecord, unsigned>& a, const std::pair<DeltaRecord, unsigned>& b)
        {
            return a.second < b.second;
        });

    return bestMatch->first;
}

DeltaRecord getDirectionWithMaxOccurence(
    const BasicKNeighborFinder::NeighborsVector& neighbors)
{

}

DeltaRecord getDirectionWithMaxOccurenceFromWeightedNeighbors(
    const BasicKNeighborFinder::NeighborsVector& neighbors)
{

}

}
