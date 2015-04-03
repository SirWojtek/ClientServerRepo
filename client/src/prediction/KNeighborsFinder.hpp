#ifndef K_NEIGHBORS_FINDER_HPP_
#define K_NEIGHBORS_FINDER_HPP_

#include <map>
#include <vector>
#include <functional>

namespace prediction
{

template<class T_input, class T_output>
class KNeighborsFinder
{
public:
    using DistanceFunction = std::function<unsigned(T_input)>;

    KNeighborsFinder(DistanceFunction func);

    void insert(const T_input& input, const T_output& output);
    void setDistanceFunction(DistanceFunction func);
    std::vector<T_output> getNeighbors(unsigned k) const;

private:
    std::map<unsigned, T_input> getInputDataScore() const;

    std::map<T_input, T_output> neighborMap_;
    DistanceFunction distanceFunc_;
};

}

#endif  // K_NEIGHBORS_FINDER_HPP_
