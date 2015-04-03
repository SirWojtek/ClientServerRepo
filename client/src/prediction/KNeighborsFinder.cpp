
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
    neighborMap_.emplace(input, output);
}

template<class T_input, class T_output>
void KNeighborsFinder<T_input, T_output>::setDistanceFunction(DistanceFunction func)
{
    distanceFunc_ = func;
}

template<class T_input, class T_output>
std::vector<T_output> KNeighborsFinder<T_input, T_output>::getNeighbors(unsigned k) const
{
    std::vector<T_output> result;
    std::map<unsigned, T_input> score = getInputDataScore();

    for (unsigned i = 0; i < k; i++)
    {
        result.emplace_back(neighborMap_.at(score.begin()->second));
        score.erase(score.begin());
    }

    return result;
}

template<class T_input, class T_output>
std::map<unsigned, T_input> KNeighborsFinder<T_input, T_output>::getInputDataScore() const
{
    std::map<unsigned, T_input> result;

    for (const auto& record : neighborMap_)
    {
        result.emplace(distanceFunc_(record.first), record.first);
    }

    return result;
}

template class KNeighborsFinder<InputRecord, DeltaRecord>;

}


