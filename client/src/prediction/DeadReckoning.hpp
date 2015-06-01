#ifndef DEAD_RECKONING_HPP_
#define DEAD_RECKONING_HPP_

#include <vector>
#include <algorithm>

namespace prediction
{

template<class T_input, class T_output>
class DeadReckoning
{
public:
    DeadReckoning(std::vector<T_output> possibleDirections):
        possibleDirections_(std::move(possibleDirections)) {}

    T_output getDeadReckoningPrediction(const T_input& input)
    {
        std::vector<float> distance;

        std::transform(possibleDirections_.begin(), possibleDirections_.end(),
            std::back_inserter(distance),
            [&input](const T_output& direction)
            {
                return std::abs(direction.deltaX - input.direction.deltaX) +
                    std::abs(direction.deltaY - input.direction.deltaY);
            });

        unsigned index = std::min_element(distance.begin(), distance.end()) - distance.begin();
        return possibleDirections_[index];
    }

private:
    std::vector<T_output> possibleDirections_;
};

}

#endif  // DEAD_RECKONING_HPP_
