
#include "KNeighborsFinder.hpp"
#include "Records.hpp"

#include <algorithm>
#include <utility>

namespace prediction
{

template<class T_input, class T_output>
KNeighborsFinder<T_input, T_output>::KNeighborsFinder(DistanceFunction distanceFunc) :
    distanceFunc_(distanceFunc) {}

template<class T_input, class T_output>
void KNeighborsFinder<T_input, T_output>::insert(const T_input& input, const T_output& output)
{
    auto neighborMapIt = neighborMap_.find(input);

    if (neighborMapIt == neighborMap_.end())
    {
        OutputHistogram temp = {{output, 1}};
        neighborMap_.emplace(input, temp);
        return;
    }

    updateExistingRecord(*neighborMapIt, output);
}

template<class T_input, class T_output>
void KNeighborsFinder<T_input, T_output>::updateExistingRecord(
    std::pair<const T_input, OutputHistogram>& record, const T_output& output)
{
    OutputHistogram& histogram = record.second;
    auto histogramIt = histogram.find(output);

    if (histogramIt == histogram.end())
    {
        histogram.emplace(output, 1);
        return;
    }

    histogramIt->second++;
}

template<class T_input, class T_output>
void KNeighborsFinder<T_input, T_output>::setDistanceFunction(DistanceFunction func)
{
    distanceFunc_ = func;
}

template<class T_input, class T_output>
typename KNeighborsFinder<T_input, T_output>::NeighborsVector
KNeighborsFinder<T_input, T_output>::getNeighbors(unsigned k) const
{
    NeighborsVector result;
    std::map<float, T_input> score = getInputDataScore();

    for (unsigned i = 0; i < k; i++)
    {
        if (score.empty())
        {
            break;
        }

        auto closestNeighbor = score.begin();
        result.emplace_back(closestNeighbor->second, neighborMap_.at(closestNeighbor->second));
        score.erase(score.begin());
    }

    return result;
}

template<class T_input, class T_output>
std::map<float, T_input> KNeighborsFinder<T_input, T_output>::getInputDataScore() const
{
    std::map<float, T_input> result;

    for (const auto& record : neighborMap_)
    {
        result.emplace(distanceFunc_(record.first), record.first);
    }

    return result;
}

template class KNeighborsFinder<InputRecord, DeltaRecord>;

}


