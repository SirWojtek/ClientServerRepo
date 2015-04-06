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
    using DistanceFunction = std::function<float(const T_input&)>;
    using OutputHistogram = std::map<T_output, unsigned>;
    using NeighborsVector = std::vector<std::pair<T_input, OutputHistogram>>;

    KNeighborsFinder(DistanceFunction func);

    void insert(const T_input& input, const T_output& output);
    void setDistanceFunction(DistanceFunction func);
    NeighborsVector getNeighbors(unsigned k) const;

private:
    std::map<float, T_input> getInputDataScore() const;
    void updateExistingRecord(
    	std::pair<const T_input, OutputHistogram>& record, const T_output& output);

    std::map<T_input, OutputHistogram> neighborMap_;
    DistanceFunction distanceFunc_;
};

}

#endif  // K_NEIGHBORS_FINDER_HPP_
