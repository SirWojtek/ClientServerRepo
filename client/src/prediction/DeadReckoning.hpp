#ifndef DEAD_RECKONING_HPP_
#define DEAD_RECKONING_HPP_

#include <vector>
#include <algorithm>
#include <limits>

namespace prediction
{

template<class T_input, class T_output>
class DeadReckoning
{
private:
    struct Result
    {
        int distance;
        T_output direction;
    };
public:
    DeadReckoning(std::vector<T_output> possibleDirections):
        possibleDirections_(std::move(possibleDirections)) {}

    T_output getDeadReckoningPrediction(const T_input& input)
    {
        std::vector<int> distance;
        Result result{std::numeric_limits<int>::max(), T_output()};

        for (const auto& direction : possibleDirections_)
        {
            int distance = std::abs(direction.deltaX - input.direction.deltaX) +
                    std::abs(direction.deltaY - input.direction.deltaY);

            if (distance < result.distance)
            {
                result.distance = distance;
                result.direction = direction;
            }
        }

        return result.direction;

        // std::transform(possibleDirections_.begin(), possibleDirections_.end(),
        //     std::back_inserter(distance),
        //     [&input](const T_output& direction)
        //     {
        //         return ;
        //     });

        // unsigned index = std::min_element(distance.begin(), distance.end()) - distance.begin();
        // return possibleDirections_[index];
    }

private:
    std::vector<T_output> possibleDirections_;
};

}

#endif  // DEAD_RECKONING_HPP_
