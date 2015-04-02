
#include "KNeighborsFinder.hpp"

#include "Records.hpp"

namespace prediction
{

template<class T_input, class T_output>
KNeighborsFinder<T_input, T_output>::KNeighborsFinder(unsigned k, CompareFunction compareFunc) :
    k_(k),
    compareFunc_(compareFunc) {}

template<class T_input, class T_output>
void KNeighborsFinder<T_input, T_output>::insert(const T_input& input, const T_output& output)
{

}

template<class T_input, class T_output>
void KNeighborsFinder<T_input, T_output>::setK(unsigned k)
{

}

template<class T_input, class T_output>
void KNeighborsFinder<T_input, T_output>::setCompareFunction(KNeighborsFinder::CompareFunction cmp)
{

}

template<class T_input, class T_output>
std::vector<T_output> KNeighborsFinder<T_input, T_output>::getNeighbors() const
{

}

template class KNeighborsFinder<InputRecord, DeltaRecord>;

}


