
#include <algorithm>

#include "DeadReckoning.hpp"

namespace prediction
{

template<class T_input, class T_output>
DeadReckoning<T_input, T_output>::DeadReckoning(std::vector<T_output> possibleDirections) :
    possibleDirections_(std::move(possibleDirections)) {}

template<class T_input, class T_output>
T_output DeadReckoning<T_input, T_output>::getDeadReckoningPrediction(const T_input& input)
{
    std::vector<decltype(T_output.deltaX)> distance;

    std::tranfsorm(possibleDirections_.begin(), possibleDirections_.end(),
        [&input](const T_output& direction)
        {
            return std::abs(direction.deltaX - input.direction.deltaX) +
                std::abs(direction.deltaY - input.direction.deltaY);
        });

    unsigned index = std::min_element(distance.begin(), distance.end()) - distance.begin();
    return possibleDirections_[index];
}

}
