#ifndef K_NEIGHBORS_FINDER
#define K_NEIGHBORS_FINDER

#include <map>
#include <vector>
#include <functional>

namespace prediction
{

template<class T_input, class T_output>
class KNeighborsFinder
{
public:
    using CompareFunction = std::function<int(const T_input& cmp)>;

    KNeighborsFinder(unsigned k, CompareFunction compareFunc);

    void insert(const T_input& input, const T_output& output);
    void setK(unsigned k);
    void setCompareFunction(CompareFunction cmp);
    std::vector<T_output> getNeighbors() const;

private:
    std::map<T_input, T_output> neighborMap_;
    const unsigned k_;
    CompareFunction compareFunc_;
};

}

#endif  // K_NEIGHBORS_FINDER
