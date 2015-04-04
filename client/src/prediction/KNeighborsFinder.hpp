#ifndef K_NEIGHBORS_FINDER_HPP_
#define K_NEIGHBORS_FINDER_HPP_

#include <map>
#include <vector>
#include <functional>
#include <utility>

namespace prediction
{

template<class T_input, class T_output>
class KNeighborsFinder
{
public:
    using DistanceFunction = std::function<int(const T_input&)>;
    using NeighborsVector = std::vector<std::pair<T_input, T_output>>;

    KNeighborsFinder(DistanceFunction func);

    void insert(const T_input& input, const T_output& output);
    void setDistanceFunction(DistanceFunction func);
    NeighborsVector getNeighbors(unsigned k) const;

private:
    std::map<int, T_input> getInputDataScore() const;

    std::map<T_input, T_output> neighborMap_;
    DistanceFunction distanceFunc_;
};

}

#endif  // K_NEIGHBORS_FINDER_HPP_
