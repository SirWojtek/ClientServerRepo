#ifndef DEAD_RECKONING_HPP_
#define DEAD_RECKONING_HPP_

#include <vector>

namespace prediction
{

template<class T_input, class T_output>
class DeadReckoning
{
public:
    DeadReckoning(std::vector<T_output> possibleDirections);

    T_output getDeadReckoningPrediction(const T_input& input);

private:
    std::vector<T_output> possibleDirections_;
};

}

#endif  // DEAD_RECKONING_HPP_
