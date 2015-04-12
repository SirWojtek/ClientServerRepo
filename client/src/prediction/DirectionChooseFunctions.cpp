
#include "DirectionChooseFunctions.hpp"
#include "Records.hpp"

#include <algorithm>

namespace prediction
{

namespace
{
    bool isDirectionInHistogram(const BasicKNeighborFinder::OutputHistogram& hist,
        const DeltaRecord& record)
    {
        return hist.find(record) != hist.end();
    }

    BasicKNeighborFinder::OutputHistogram getMergedHistogram(
        const BasicKNeighborFinder::NeighborsVector& neighbors)
    {
        BasicKNeighborFinder::OutputHistogram result;

        for (const auto& neighbor : neighbors)
        {
            for (const auto& histogram : neighbor.second)
            {
                if (!isDirectionInHistogram(result, histogram.first))
                {
                    result[histogram.first] = 0;
                }
                result[histogram.first] += histogram.second;
            }
        }

        return result;
    }

    DeltaRecord getMaxHistogramRecord(const BasicKNeighborFinder::OutputHistogram& histogram)
    {
        auto bestMatch = std::max_element(histogram.begin(), histogram.end(),
            [](const std::pair<DeltaRecord, unsigned>& a, const std::pair<DeltaRecord, unsigned>& b)
            {
                return a.second < b.second;
            });

        return bestMatch->first;
    }
}

DeltaRecord getClosestNeighborDirectionWithMaxOccurence(
    const BasicKNeighborFinder::NeighborsVector& neighbors)
{
    BasicKNeighborFinder::OutputHistogram histogram = neighbors[0].second;
    return getMaxHistogramRecord(histogram);
}

DeltaRecord getDirectionWithMaxOccurence(
    const BasicKNeighborFinder::NeighborsVector& neighbors)
{
    BasicKNeighborFinder::OutputHistogram histogram = getMergedHistogram(neighbors);
    return getMaxHistogramRecord(histogram); // :**
}

// DeltaRecord getDirectionWithMaxOccurenceFromWeightedNeighbors(
//     const BasicKNeighborFinder::NeighborsVector& neighbors)
// {

// }

}
